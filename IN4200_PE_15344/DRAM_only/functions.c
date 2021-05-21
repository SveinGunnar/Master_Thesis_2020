#include "functions.h"

void read_graph_from_file(char filename[]){
	int i, j, k, temp;
	FILE *fp = fopen( filename, "r" );
	char str[100];
	
	//First and second line in file are thrown away
	if( fgets(str, 100, fp) == NULL ) printf("ERROR\n");
	if( fgets(str, 100, fp) == NULL ) printf("ERROR\n");

	//Extract Nodes and edges from the third line.
	if( fgets(str, 100, fp) == NULL ) printf("ERROR\n");
	char * wordPointer;
	wordPointer = strtok (str," ");
	int line3_counter = 0;
	while (wordPointer != NULL){
		line3_counter++;
		if(line3_counter == 3)
			nodes = atoi(wordPointer);
		else if(line3_counter == 5)
			edges = atoi(wordPointer);
		wordPointer = strtok (NULL, " ");
	}
	//Throws away the forth line.
	if( fgets(str, 100, fp) == NULL ) printf("ERROR\n");
	
	//Loads the rest of the files.
	int *row_nodes_occurrence = (int*)calloc(nodes, sizeof(int));
	int *column_nodes_occurrence = (int*)calloc(nodes, sizeof(int));

	//Creates a 2d array with dimension n x 3.
	int **CCS = (int**)malloc(edges*sizeof(int*));
	for ( i=0; i<edges; i++)
		CCS[i] = (int*)malloc(3*sizeof(int));
	double *CCS_values = (double*)malloc(edges*sizeof(double));
	
	//Feeds the filestream into the newly created array.
	int fromNode, toNode;
	for( i=0; i<edges; i++){
		//fgets(str, 100, fp);
		if( fgets(str, 100, fp) == NULL ) printf("ERROR\n");
		fromNode = atoi(strtok(str,"\t"));
		toNode = atoi(strtok(NULL,"\t"));

		CCS[i][0] = fromNode;
		CCS[i][1] = toNode;
		CCS[i][2] = row_nodes_occurrence[toNode];
		row_nodes_occurrence[toNode]++;
		column_nodes_occurrence[fromNode]++;
	}

	//Adds values to the matrix.
	//Counts the number of outgoing links from node and add 1/sum to all Nodes
	//in the coulumn.
	j=0;
	int sum=0;
	double d;
	for( i=0; i<nodes; i++){
		sum += column_nodes_occurrence[i];
		d = 1.0/column_nodes_occurrence[i];
		for( ; j<sum; j++){
			CCS_values[j] = d;
		}
	}

	//Finding all the dangling websites and
	//places the indices in an array called dangling_webpages.
	dwp_size = 0;
	for ( i=0; i<nodes; i++)
		if( column_nodes_occurrence[i] == 0)
			column_nodes_occurrence[dwp_size++] = i;
	//Puts the dangling websites into a smaller array.
	dwp = (int*)malloc(dwp_size*sizeof(int));
	for ( i=0; i<dwp_size; i++){
		dwp[i] = column_nodes_occurrence[i];
	}
	
	//Convert the CCS into a CRS.
	//CRS_row_ptr = (int*)malloc((edges+1)*sizeof(int));
	CRS_row_ptr = (int*)calloc((edges+1), sizeof(int));
	//CRS_col_idx = (int*)malloc(edges*sizeof(int));
	CRS_col_idx = (int*)calloc((edges), sizeof(int));
	CRS_values = (double*)malloc(edges*sizeof(double));

	//Adds the indices for col_idx into the row_ptr
	CRS_row_ptr[0] = 0;
	for( i=1; i<nodes; i++){
		CRS_row_ptr[i] = CRS_row_ptr[i-1] + row_nodes_occurrence[i-1];
	}
	CRS_row_ptr[nodes] = edges; //Adds the index of last node in node-1.

	//Adds columns into col_idx and values to CRS_values
	for( i=0; i<edges; i++){
		temp = CRS_row_ptr[CCS[i][1]]+CCS[i][2];
		CRS_col_idx[temp] = CCS[i][0];
		CRS_values[temp] = CCS_values[i];
	}

	//free up memory
	free(column_nodes_occurrence);
	for ( i=0; i<edges; i++)
		free(CCS[i]);
	free(CCS);
	free(CCS_values);
	free(row_nodes_occurrence);
}

void PageRank_iterations(){
	double d=0.99;
	double e=0.0000000000000000021413;

	int num_threads;

	int testVariable=0;

	double Wk_1; //W^k-1 This is the scalar value for dangling webpages.
	double Wk_1_product; //part one of x^k formula.
	double *temp_x; //Will be using this when swapping x and x^k-1

	//one minus d
	double omd = 1.0-d;
	//inverse N
	double iN = 1.0/nodes;
	//x^k-1
	//xk_1 = (double*)malloc(nodes*sizeof(double));
	//x^k
	//x = (double*)malloc(nodes*sizeof(double));
	//double *testArray = (double*)malloc(nodes*sizeof(double));

	//This variable will be compared against the convergence threshold value
	//double *diffX;
	//double diffX_scalar;
	double diff=0.0;

	double average=0.0;
	double sumSquare = 0.0;
	double test1 = 0.0;
	double test2 = 0.0;

        //int *maximum; // = (int*)calloc(size, sizeof(int));
        //int *minimum;
	int size;
	int maximum_index=0, minimum_index=0;

	//Counts the number of iterations.
	int n=0;
	//int i;
	int iteration_size=1;
	//double tt;
	double idle_time=0.0;
        double temp_time;
        double data_generation_time;
	double analyze_time=0.0, temp_calc;
	Wk_1=1;

	//printf("test123\n");

	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
			//printf("Number of iter threads %d\n", num_threads);
			//diffX = (double*)malloc(num_threads*sizeof(double));
			
			//For calculation
			//size = omp_get_num_threads();
                        //maximum = (int*)calloc(size, sizeof(int));
                        //minimum = (int*)calloc(size, sizeof(int));
                        //average_vector = (double*)calloc(size, sizeof(double));
			//printf("sdf");
		}
		
		//printf("sadf\n");
		//int thread_id = omp_get_thread_num();
		int i,j;

		//Adds values to x^0.
		#pragma omp for
		for( i=0; i<nodes; i++){
			xk_1[i] = iN;
			x[i] = iN;
		}

		#pragma omp single
                {
			//printf("sadf\n");
			data_generation_time = mysecond();
		}
		

		double double_temp;
		while( n<5000 ){
			#pragma omp barrier
			#pragma omp single
			{
				n++;
				diff=0.0;
				average = 0;
				//completes the first part of the formula.
                                Wk_1_product = (omd + (d*Wk_1))*iN;
			}


			//Computing the x^k formula
			//diffX[thread_id]=0;
			#pragma omp for reduction(max:diff) reduction(+:testVariable)
			for( i=0; i<nodes; i++){
				//This is A*x^k-1
				double_temp = 0;
				for( j=CRS_row_ptr[i]; j<CRS_row_ptr[i+1]; j++){
					double_temp += CRS_values[j] * xk_1[CRS_col_idx[j]];
				}
				//d*Ax^k-1
				double_temp *= d;
				//Adding the first part and second part together.
				double_temp += Wk_1_product;
				x[i] = double_temp;

				//Comuting the difference between x^k and x^k-1
				//and adds the biggest diff to diffX[thread_id]
				if( x[i]-xk_1[i] > diff ){
					diff = x[i] - xk_1[i];
				}
			}
			


			//calculation
			#pragma omp barrier
			#pragma omp single
			{
				temp_x = xk_1;
                                xk_1 = x;
                                x = temp_x;
				//starting time measurement of calculation.
				temp_calc=mysecond();
			}

			//Analyse part
			#pragma omp for reduction(+ : average)
                       	for(i=0;i<nodes;i++){
                       		average += xk_1[i];
                       	}
			#pragma omp for reduction(+ : average)
			for(i=0;i<nodes;i++){
                           	average += xk_1[i];
                    	}

			#pragma omp for reduction(+ : average)
                     	for(i=0;i<nodes;i++){
                          	average += xk_1[i];
                    	}

			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){
                        	average += xk_1[i];
                     	}

			#pragma omp for reduction(+ : average)
                     	for(i=0;i<nodes;i++){
                         	average += xk_1[i];
                    	}

			#pragma omp barrier
			#pragma omp single
			{
				average *= iN;
				analyze_time+=mysecond()-temp_calc;
			}
		}//end of while-loop
		#pragma omp single
        	{
			data_generation_time = mysecond() - data_generation_time;
            	}
	}//End parallel
	free(dwp);
        free(x);
        free(xk_1);
        free(CRS_row_ptr);
        free(CRS_col_idx);
        free(CRS_values);
	//iteration_time = mysecond() - iteration_time;
	//printf("Threads, Total time, Iteration time, Calculation time\n");
        printf("%d,%f,%f,%f\n", max_threads, data_generation_time, data_generation_time-analyze_time, analyze_time);
	//For testing:
	//printf("iterations: %d\n", n);
	//printf("%f, %f, %f %f\n", average, sumSquare, test1, test2);
	//printf("temp_counter_double: %f\n", temp_counter_double);
	//printf("temp_counter_int: %f\n", temp_counter_ana);
	//printf("testVariable %d\n", testVariable);
}

double mysecond(){
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
