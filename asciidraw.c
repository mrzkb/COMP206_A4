#include <stdio.h>
#include <string.h>
#include <math.h>
//Mira Kandlikar-Bloch, mira.kandlikar-bloch@mail.mcgill.ca 

int main() 
{
	char grid[1000][1000];
	char command[100];
      	char command2[100];	
	int width, height;
       	int is_grid; //keep track of if grid command has been called 	
	char CHAR='*'; 
	fgets(command,100,stdin);

	while (strncmp(command, "END", strlen("END"))!=0){ //while the end command has not been given 
		
		if(strncmp(command, "GRID ", strlen("GRID "))==0){ //if grid command
			if(is_grid==1){ //if the grid command has already been called 
				printf("GRID was already set to %d,%d.", width, height);
			}
			else{
				sscanf(command,"%s %d %d",command2,&width, &height);
				is_grid=1; 
			}

			if(width>1000 || height>1000){ //if width or height is greater than grid size 
				is_grid=0;
				puts("Sorry, width and height must be no greater than 1000.");
			}
		}
		else if(strncmp(command, "CHAR ", strlen("CHAR "))==0) {
			sscanf(command,"%s %c",command2,&CHAR); //stores new character in CHAR 
		}
		else if(strncmp(command, "DISPLAY", strlen("DISPLAY"))==0){ 
			if(is_grid==1){
				int x_axis=0;
				int y_axis=height%10-1; //height is one digit so graph isn't changed 
											 
				for(int r=height-1; r>=-1; r--){	
					for(int f=-1; f<=width-1; f++){
						if(r==-1){
							if(f!=-1){
								if(x_axis==10) x_axis=0; //keep width at one digit
								printf("%d",x_axis);
								x_axis++;
							}
							if(f==-1) putchar(' ');
						} 
						else if(r!=-1 && f==-1){
							if(y_axis==-1) y_axis=9;//keep height at one digit 
							printf("%d",y_axis);
							y_axis--;
						}	
							
						else if(grid[f][r]!=0) putchar(grid[f][r]); //if the element of grid is not empty print the element 
						else putchar(' ');//if it is empty print a space 
					}
					putchar('\n');
				}
			}	
			else puts("Only CHAR command is allowed before the grid size is set.");
		}
		else if(strncmp(command, "RECTANGLE ", strlen("RECTANGLE "))==0) { 
			if(is_grid==1){
	       			char xy1[10];
                        	char xy2[10];
                        	int x1;
                        	int y1;
                        	int x2;
                        	int y2;
                        	sscanf(command,"%s %s %s",command2, xy1, xy2);//stores coordinates 
                        
				char* s=strtok(xy1, ","); //splits string at comma
                        	sscanf(s,"%d",&x1); //converts string to int 
	
        	                char* a=strtok(NULL, ",");
                	        sscanf(a,"%d",&y1);
	
        	                char* q=strtok(xy2, ",");
                	        sscanf(q,"%d",&x2);

                        	char* u=strtok(NULL, ",");
	                        sscanf(u,"%d",&y2);
			
				for(int i=x1; i<=x2; i++){ //prints horizontal lines of rectangle 
					if(i>=0 && i<=1000 && y1>=0 && y1<=1000 && y2>=0 && y2<=1000){ 
					grid[i][y1]=CHAR;
					grid[i][y2]=CHAR;
					}
				}

				for(int k=y2; k<=y1; k++){ //prints vertical lines of rectangle 
					if(k>=0 && k<=1000 && x1>=0 && x1<=1000 && x2>=0 && x2<=1000){
					grid[x1][k]=CHAR;
					grid[x2][k]=CHAR;
					}
				}
		
			}
			else puts("Only CHAR command is allowed before the grid size is set.");
		}		

	       else if(strncmp(command, "LINE ", strlen("LINE "))==0){	
		       if(is_grid==1){
		        	char xy1[100];
	       			char xy2[100];
				int x1;
				int y1; 
				int x2;
				int y2;
			
				sscanf(command,"%s %s %s",command2, xy1, xy2);
			
				char* s=strtok(xy1, ",");//splits string at comma 
				sscanf(s,"%d",&x1); //converts string to int 
			
				char* a=strtok(NULL, ",");
				sscanf(a,"%d",&y1);

				char* q=strtok(xy2, ",");
				sscanf(q,"%d",&x2);

				char* u=strtok(NULL, ",");
				sscanf(u,"%d",&y2);
			
				if(fabs(y1-y2)>fabs(x1-x2)){
			
			      		if(y2>y1){ //loop has to start at x1 
                        	        	float x= x2-x1;
                        	        	float y= y2-y1;
              	                		float m= x/y;//slope of line 
                                		float b=x1-m*y1;//intercept 

                                		for(int k=y1; k<=y2; k++){
                                        		int t=round(m*k+b);//value of y in y=mx+b 
                                        		if(k>=0 && k<=1000 && t>=0 && t<=1000) grid[t][k]=CHAR; //elements of grid corresponding to line =CHAR 
                                		}

                        		}
                        		else if(y2<y1){ //loop has to start at x2 
                                		float x= x1-x2;
                                		float y= y1-y2;
                                		float m= x/y;
                                		float b=x1-m*y1;
                                		for(int z=y2; z<=y1; z++){
                                        		int t=round(m*z+b);
							if(z>=0 && z<=1000 && t>=0 && t<=1000) grid[t][z]=CHAR;
						}

			
					}
				}

				if(x2>x1){ //loop has to start at x1 
					float x= x2-x1; 
					float y= y2-y1;
		       			float m= y/x;//slope of line 
					float b=y1-m*x1;//intercept 
			
					for(int k=x1; k<=x2; k++){
						int t=round(m*k+b);//value of y in y=mx+b 
						if(k>=0 && k<=1000 && t>=0 && t<=1000) grid[k][t]=CHAR; //elements of grid corresponding to line =CHAR 
					}			

				}
				else if(x2<x1){ //loop has to start at x2 
					float x= x1-x2;
					float y= y1-y2;
					float m= y/x;
					float b=y1-m*x1; 
					for(int z=x2; z<=x1; z++){
						int t=round(m*z+b);
						if(z>=0 && z<=1000 && t>=0 && t<=1000) grid[z][t]=CHAR; 
					}	
				}
				
				else{	 			//vertical line 
					if(y2>y1){ //loop has to start at y1 
						for(int s=y1; s<=y2; s++){
							if(s>=0 && s<=1000 && x1>=0 && x1<=1000) grid[x1][s]=CHAR;
						}
					}	
					if(y1>y2){ //loop has to start at y2
						for(int w=y2; w<=y1; w++){
							if(w>=0 && w<=1000 && x1>=0 && x1<=1000) grid[x1][w]=CHAR;	
						}
					}	
					else{
				 		if(x1>=0 && x1<=1000 && y1>=0 && y1<=1000) grid[x1][y1]=CHAR;
					}
				}
		       			
			}
		       else puts("Only CHAR command is allowed before the grid size is set.");
		}

		else if(strncmp(command, "CIRCLE ", strlen("CIRCLE "))==0){
			if(is_grid==1){
				char xy[100]; 
				int x;
				int y;
				int r;
				int x1;
				int y1; 

				sscanf(command,"%s %s %d",command2,xy,&r);
			
				char* a=strtok(xy, ",");
				sscanf(a,"%d",&x);

				char* q=strtok(NULL, ",");
				sscanf(q,"%d",&y);
				
				if(r<1) puts("Valid values for r are at least 1.");
			
				else{ //these are the points at the top center of the circle 
					 x1=x;
				 	y1=y+r;

					while(x1<=(x+r) && y1>=y){
					
						if(x1>=0 && x1<=1000 && y1>=0 && y1<=1000) grid[x1][y1]=CHAR;//first quadrant 
						if(x1>=0 && x1<=1000 && (y1-2*(y1-y))>=0 && (y1-2*(y1-y))<=1000) grid[x1][y1-2*(y1-y)]=CHAR;//reflection into 4th quadrant
						if((x1-2*(x1-x))>=0 && (x1-2*(x1-x))<=1000 && y1>=0 && y1<=1000) grid[x1-2*(x1-x)][y1]=CHAR;//reflection into second quadrant 
						if((x1-2*(x1-x))>=0 && (x1-2*(x1-x))<=1000 && (y1-2*(y1-y))>=0 && (y1-2*(y1-y))<=1000) grid[x1-2*(x1-x)][y1-2*(y1-y)]=CHAR;//reflection into 3rd quadrant 
				
						float c1=sqrt(pow((x1-x),2)+pow((y1-y-1),2)); //distance from original x,y to c1 
						float c2=sqrt(pow((x1-x+1),2)+pow((y1-y),2)); //distance from original x,y to c2 
						float c3=sqrt(pow((x1-x+1),2)+pow((y1-y-1),2));//distance from original x,y to c3

						float d1=fabs(c1-r);//abs of difference between c1 and radius 
						float d2=fabs(c2-r);
						float d3=fabs(c3-r);

						//these statements find which difference is the smallest 
						if(d1>d2 && d2>d3){
							x1=x1+1;
							y1=y1-1;
						}
					
						else if(d1>d2 && d3>=d2) x1=x1+1;

						else if(d2>d1 && d1>d3){
							x1=x1+1;
							y1=y1-1;
						}
	
						else if(d2>d1 && d3>=d1) y1=y1-1;
	
						else if(d3>d1 && d1>d2) x1=x1+1;

						else if(d3>d1 && d2>=d1) y1=y1-1;	
					}
				
					
				}
				
			}
			else puts("Only CHAR command is allowed before the grid size is set.");
		
		}
		else printf("Error did not understand %s", command);		
	fgets(command,100,stdin);
	}
	
}
