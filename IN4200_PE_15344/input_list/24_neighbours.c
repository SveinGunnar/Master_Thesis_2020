#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void addLine(FILE **fp){
//        fprintf(fp, "hahahahhahahhaha\n" );
//}


int main(int argc, char *argv[]) {
        int n = atoi(argv[1]);
        //int naboer = atoi(argv[2]);
        int i,j;
        int k,l;
        //int n=10; //2000; //Totalt 4'000'000 
        int e=16000000;
        int kanter= 24*(n-4)*(n-4)+4*19*(n-4)+4*14*(n-4)+8*11+4*15+4*8;

        FILE *fp;
        fp = fopen( argv[2], "w+");
	//printf("testing\n");
	//addLine(fp);
        fprintf(fp, "#This is a test\n");
        fprintf(fp, "#This is a test\n");
        fprintf(fp, "# Nodes: %d Edges: %d\n", (n*n), kanter);
        fprintf(fp, "# FromNodeId       ToNodeId\n");
	
	
	for( i=0; i<n; i++){
                for( j=0; j<n; j++){
                        if( i==0 ){
                                if( j==0 ){
					for( k=i; k<=i+2; k++){
                                                for( l=j; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==1 ){
					for( k=i; k<=i+2; k++){
                                                for( l=j-1; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==n-2 ){
					for( k=i; k<=i+2; k++){
                                                for( l=j-2; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){
					for( k=i; k<=i+2; k++){
                                                for( l=j-2; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{
					for( k=i; k<=i+2; k++){
                                                for( l=j-2; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }
			}else if ( i==1 ){
				if( j==0 ){
					for( k=i-1; k<=i+2; k++){
                                                for( l=j; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==1 ){
					for( k=i-1; k<=i+2; k++){
                                                for( l=j-1; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-2 ){
					for( k=i-1; k<=i+2; k++){
                                                for( l=j-2; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){
					for( k=i-1; k<=i+2; k++){
                                                for( l=j-2; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{
					for( k=i-1; k<=i+2; k++){
                                                for( l=j-2; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }
			}else if ( i==n-2 ){
				if( j==0 ){
					for( k=i-2; k<=i+1; k++){
                                                for( l=j; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==1 ){
					for( k=i-2; k<=i+1; k++){
                                                for( l=j-1; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-2 ){
					for( k=i-2; k<=i+1; k++){
                                                for( l=j-2; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){
					for( k=i-2; k<=i+1; k++){
                                                for( l=j-2; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{
					for( k=i-2; k<=i+1; k++){
                                                for( l=j-2; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }
			}else if ( i==n-1 ){
                                if( j==0 ){
					for( k=i-2; k<=i; k++){
                                                for( l=j; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==1 ){
					for( k=i-2; k<=i; k++){
                                                for( l=j-1; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==n-2 ){
					for( k=i-2; k<=i; k++){
                                                for( l=j-2; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){
					for( k=i-2; k<=i; k++){
                                                for( l=j-2; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{
					for( k=i-2; k<=i; k++){
                                                for( l=j-2; l<=j+2; l++){
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
                                if( j==0 ){
					for( k=i-2; k<=i+2; k++){
                                                for( l=j; l<=j+2; l++){
                                                	if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==1 ){
					for( k=i-2; k<=i+2; k++){
                                                for( l=j-1; l<=j+2; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
				}else if ( j==n-2 ){
					for( k=i-2; k<=i+2; k++){
                                                for( l=j-2; l<=j+1; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else if ( j==n-1 ){
					for( k=i-2; k<=i+2; k++){
                                                for( l=j-2; l<=j; l++){
                                                        if( k==i && l==j){
                                                                //do nothing;
                                                        }else{
                                                                fprintf(fp, "%d\t%d\n", ((n*i)+j), ((n*k)+l) );
                                                        }
                                                }
                                        }
                                }else{
					for( k=i-2; k<=i+2; k++){
                                                for( l=j-2; l<=j+2; l++){
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
