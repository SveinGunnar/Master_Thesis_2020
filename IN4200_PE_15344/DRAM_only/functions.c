#include "functions.h"

void read_graph_from_file(char filename[]){
	int i, j, k, temp;
	FILE *fp = fopen( filename, "r" );
	char trashbin[100];
	char str[100];

	//First and second line in file are thrown away
	if( fgets(str, 100, fp) == NULL ) return;
	if( fgets(str, 100, fp) == NULL ) return;

	//Extract Nodes and edges from the third line.
	if( fgets(str, 100, fp) == NULL ) return;;
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
	if( fgets (str, 100, fp) == NULL ) return;

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
		if( fgets(str, 100, fp) == NULL ) return;
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
	CRS_row_ptr = (int*)malloc((edges+1)*sizeof(int));
	CRS_col_idx = (int*)malloc(edges*sizeof(int));
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

void PageRank_iterations(double d, double e){
	int num_threads;

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

	//This variable will be compared against the convergence threshold value
	double *diffX;
	double diffX_scalar;

	//Counts the number of iterations.
	int n=0;
	int i;
	//double tt;
	double idle_time=0.0;
        double temp_time;
        double iteration_time = mysecond();

	#pragma omp parallel num_threads(iter_threads)
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
			//printf("Number of iter threads %d\n", num_threads);
			diffX = (double*)malloc(num_threads*sizeof(double));
		}

		int thread_id = omp_get_thread_num();
		int j;

		//Adds values to x^0.
		#pragma omp for
		for( i=0; i<nodes; i++)
			xk_1[i] = iN;

		while( 1==1 ){
			#pragma omp single
			{
				n++;
				//x^k becomes x^k-1
				//temp_x = xk_1;
				//xk_1 = x;
				//x = temp_x;

				//Sum of all dangling websites. W^k-1
				Wk_1=0;
				for( i=0; i<dwp_size; i++)
					Wk_1 += xk_1[ dwp[i] ];

				//completes the first part of the formula.
				Wk_1_product = (omd + (d*Wk_1))*iN;
			}

			//Computing the x^k formula
			diffX[thread_id]=0;
			#pragma omp for
			for( i=0; i<nodes; i++){
				//This is A*x^k-1
				x[i] = 0;
				for( j=CRS_row_ptr[i]; j<CRS_row_ptr[i+1]; j++){
					x[i] += CRS_values[j] * xk_1[CRS_col_idx[j]];
				}
				//d*Ax^k-1
				x[i] *= d;
				//Adding the first part and second part together.
				x[i] += Wk_1_product;

				//Comuting the difference between x^k and x^k-1
				//and adds the biggest diff to diffX[thread_id]
				if( x[i]-xk_1[i] > diffX[thread_id] )
					diffX[thread_id] = x[i] - xk_1[i];
			}
			
			//
			#pragma omp single
			{
				temp_time = mysecond();
				idle_time += mysecond() - temp_time;
				//tt = mysecond();
				temp_x = xk_1;
                                xk_1 = x;
                                x = temp_x;
			}
			//#pragma omp for
                        //for(i=0; i<nodes; i++){
                        //        D_RW(nvm_values)[i]=x[i];
                        //}

			#pragma omp single
			{
				//Turns the vector into a scalar
				diffX_scalar = 0;
				for( i=0; i<num_threads; i++)
					if( diffX[i] > diffX_scalar )
						diffX_scalar = diffX[i];
			}

			//stopping criterion.
			if( diffX_scalar < e){
				break;
			}
		}//end of while-loop
	}//End parallel
	iteration_time = mysecond() - iteration_time;
        printf("Iteration: Work time: %f, idle time: %f, total time: %f\n", iteration_time-idle_time, idle_time, iteration_time);
	//For testing:
	//printf("iterations: %d\n\n", n);
}

//TOID(double) *nvm_values;
void transfer_DRAM_to_NVM(){
        int i;
	int size;
	int maximum_index=0, minimum_index=0;
	double average=0.0;
	double *average_vector; // = (double*)calloc(size, sizeof(double));
        int *maximum; // = (int*)calloc(size, sizeof(int));
	int *minimum; // = (int*)calloc(size, sizeof(int));
	//double tt;
        //double tt = mysecond();
	double idle_time=0.0;
        double temp_time;
        double transfer_time = mysecond();
        #pragma omp parallel num_threads(iter_threads)
        {
		#pragma omp single
		{
			size = omp_get_num_threads();
			maximum = (int*)calloc(size, sizeof(int));
			minimum = (int*)calloc(size, sizeof(int));
			average_vector = (double*)calloc(size, sizeof(double));
		}
		int thread_id = omp_get_thread_num();
                while(1==1){

			//Transfer array to nvdimm.
                        //#pragma omp for
                        //for(i=0; i<nodes; i++){
                        //        D_RW(nvm_values)[i]=x[i];
                        //}
			
			//maximum, minimum and average.
			#pragma omp for
                        for(i=0;i<nodes;i++){
                                if( xk_1[i] > xk_1[ maximum[thread_id] ] )
                                        maximum[thread_id] = i;
				if( xk_1[i] < xk_1[ minimum[thread_id] ] )
					minimum[thread_id] = i;
				average_vector[thread_id] += xk_1[i];
                        }
			
			#pragma omp single
			{
				//converts the vectors into scalars.
				for(i=0;i<size; i++){
                			//printf("enkelt time: %lf\n", D_RO(nvm_values)[a[i]] );
                			if( xk_1[maximum[i]] > xk_1[maximum[maximum_index]] )
                        			maximum_index = i;
					if( xk_1[maximum[i]] < xk_1[maximum[maximum_index]] )
                                                minimum_index = i;
					average += average_vector[i];
        			}
				average /= nodes;
				//printf("Top n is: %d and has value %lf\n", maximum[maximum_index], xk_1[maximum[maximum_index]]);
				//printf("Min n is: %d and has value %lf\n", minimum[minimum_index], xk_1[minimum[minimum_index]]);
				//printf("The average value is %lf\n", average);
			}

			if(iteration_ongoing==0)
                                break;
                }
        }
	transfer_ongoing = 0;
	transfer_time = mysecond() - transfer_time;
        printf("Transfer: Work time: %f, idle time: %f, total time: %f\n", transfer_time-idle_time, idle_time, transfer_time);
	
	//printf("top_n time: %lf\n", tt );
        //printf("nvm time: %lf\n", tt );
} 


int top_n(){
        int i;
        int size = max_threads;
        int x_index=0;
	int *a = (int*)calloc(size, sizeof(int));
	//double tt;

        #pragma omp parallel num_threads(max_threads)
        {
                int thread_id = omp_get_thread_num();
		while( iteration_ongoing==1 )
		{
			#pragma omp single
			{
				omp_set_lock(&lock_c);
				//tt = mysecond();
			}

                	#pragma omp for
                	for(i=0;i<nodes;i++){
                	        if( xk_1[i] > xk_1[ a[thread_id] ] )
                	                a[thread_id] = i;
                	}
			if(transfer_ongoing==0)
                        	break;
			#pragma omp single
			{
				//tt = mysecond()-tt;
				omp_unset_lock(&lock_a);
			}
		}

        }
	omp_unset_lock(&lock_a);
	//printf("a[index]: %d\n", a[x_index] );
        for(i=0;i<size; i++){
		//printf("enkelt time: %lf\n", D_RO(nvm_values)[a[i]] );
                if( xk_1[a[i]] > xk_1[a[x_index]] )
                        x_index = i;
        }
        //printf("a[index]: %d\n", a[x_index] );
        return a[x_index];
}

void top_n_webpages(int n){
	int num_threads;
	int m = 0;
	//index of the biggest nodes and their values.
	int *result_index;
	double *result_value;
	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
			result_index = (int*)malloc((num_threads*n)*sizeof(int));
			result_value = (double*)malloc((num_threads*n)*sizeof(double));
		}
		//Each thread creates their own array with index of the biggest
		//nodes and their values.
		int thread_id = omp_get_thread_num();
		int *index = (int*)calloc(n, sizeof(int));
		double *value = (double*)calloc(n, sizeof(double));

		int i,j;
		int lvi = 0; //Index of the lowest value in index array.
		int len=0;

		//Finds the n highest nodes in the array.
		#pragma omp for
		for( i=0; i<nodes; i++){
			if( x[i] > value[lvi]){
				if(value[lvi]==0)
					len++;

				value[lvi] = x[i];
				index[lvi] = i;

				//Finds the index of node with the lowest value in the index array.
				for( j=0; j<n; j++){
					if( value[j] < value[lvi] ){
						lvi = j;
					}
				}
			}
		}

		if( len>n )
			len=n;

		//Merge all the index and value arrays into two arrays called
		//result_index and result_value.
		#pragma omp critical
		{
			int a = m+len;
			for( i=0; i<len; i++){
				result_index[m+i] = index[i];
				result_value[m+i] = value[i];
			}
			m+=len;
		}
	}//End of parallell.

	//The n highest nodes will be added to this array.
	int *n_index = (int*)calloc(n, sizeof(int));
	double *n_value = (double*)calloc(n, sizeof(double));

	int i,j;
	int lvi = 0;

	//Sort the arrays from highest to lowest, but only until n
	//highest values have been found.
	int tempi;
	double tempd;
	for( i=0; i<n; i++){
		for( j=i; j<m; j++){
			if( result_value[i] < result_value[j] ){
				tempi = result_index[i];
				result_index[i] = result_index[j];
				result_index[j] = tempi;

				tempd = result_value[i];
				result_value[i] = result_value[j];
				result_value[j] = tempd;
			}
		}
	}
	//Transfer the n highest values to a new array.
	for( i=0; i<n; i++){
		n_index[i] = result_index[i];
		n_value[i] = result_value[i];
	}

	printf("n_index, n_value:\n");
	for( i=0; i<n; i++){
		printf("%d, %f\n", n_index[i], n_value[i]);
	}
}

double mysecond(){
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
