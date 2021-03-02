#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// argv[1] 2d array size.
// argv[2] textfile name.
int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
        //int naboer = atoi(argv[2]);
	int i,j;
	int k,l;
	//int n=10; //2000; //Totalt 4'000'000 
	int e=16000000;
	int kanter= (((n-2)*(n-2))*8)+((n-2)*20)+(4*3);

	FILE *fp;
        fp = fopen( argv[2], "w+");
	fprintf(fp, "#This is a test\n");
	fprintf(fp, "#This is a test\n");
	fprintf(fp, "# Nodes: %d Edges: %d\n", (n*n), kanter);
	fprintf(fp, "# FromNodeId	ToNodeId\n");

	for( i=0; i<n; i++){
		for( j=0; j<n; j++){
			if( i==0 ){
				if( j==0 ){ //3
					for( k=i; k<=i+1; k++){
                                                for( l=j; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
	                        }else if ( j==n-1 ){ //3
					for( k=i; k<=i+1; k++){
                                                for( l=j-1; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                        	}else{ //(n-2)*5
					for( k=i; k<=i+1; k++){
                                                for( l=j-1; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                        	}
			}else if ( i==n-1 ){
				if( j==0 ){ //3
					for( k=i-1; k<=i; k++){
                                                for( l=j; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){ //3
					for( k=i-1; k<=i; k++){
                                                for( l=j-1; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{ //(n-2)*5
					for( k=i-1; k<=i; k++){
                                                for( l=j-1; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }
			}
			else{
				if( j==0 ){ //(n-2)*5
					for( k=i-1; k<=i+1; k++){
                                                for( l=j; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){ //(n-2)*5
					for( k=i-1; k<=i+1; k++){
                                                for( l=j-1; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{ //((n-2)^2)*8
					for( k=i-1; k<=i+1; k++){
                                                for( l=j-1; l<=j+1; l++){
							if( k==i && l==j){
								//do nothing;
							}else{
                                                        	fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
							}
						}
					}
                                }
			}
		}
	}
	fclose(fp);	
	printf("Det er %d noder og %d kanter\n", (n*n), kanter);
	return 0;
}
