/*          Jan Zboril
 *          xzbori20
 *          FIT VUT Brno
 *          IZP 2019/2020
 *          Projekt 2 - Iteracni vypocty
 *          1. 12. 2019 
 */

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/*constants
    I_0 and U_T are defined by manufacturer of diode
    */
#define I_0 1e-12
#define U_T 0.0258563

/*function Function_Error()
    *called when someting has gone wrong
    * prints "Error" to stderr then terminates
    * programme with return value of 1
    */
void Function_Error(){
    fprintf(stderr,"Chyba\n");
}
 
/*
    *function Convert()
    * uses function sscanf() to convert string (argv) to
    * double (number used in diode()
    */ 
double Convert(char **string){
    double number;
    int chyba;
    //printf("%s\n",*string);           debugging print
    chyba=sscanf(*string,"%lf",&number);
    if(chyba!=1){
        Function_Error();   //sscanf return int with value of amount of successfull scans
	return 1;
    }
    if(number<0){
        Function_Error();               //sscanf return int with value of amount of successfull scans
	return 1;
    }
    //printf("%g\n",number);            debugging print  
    return number;
}

/*fuction diode()
    * Returns value of U_p whisch is voltage of the diode if the right value of I_p 
    * (current in diode) and I_R (current in resistor) is within the margain of eps (Epsilon).
    * Because the diode and the resistor are cennected in serial they should have the same current flowing
    * through each oif them.
    * Function uses the method of half of interval to determine the right amount of Voltage on diode.
    */
double diode(double u0, double r, double eps){

    double interval_left=0;
    double interval_right=u0;
    double U_p=u0;
    double I_p,I_R;
    double Up_old;
    
    /*	debugging prints
    printf(" %lf  %lf",u0,U_p);
    printf("\n %g %g\n",I_0,U_T);
    */
    
    do{
        Up_old=U_p;
        U_p=(interval_left+interval_right)/2.;          //chooses voltage U_p used in next line by halfing of interval
        I_p=I_0*(exp(U_p/U_T)-1.);                      //Shockley equation
        I_R=(u0-U_p)/r;                                 //Ohm formula
        
        if(I_p<I_R){                                    //I_p should be equal to I_R
            interval_left=U_p;
        }
        else{
            interval_right=U_p;
        }
        
        // debugging print 
        //printf(" up %lf  ip %lf   ir %lf\n", U_p,I_p,I_R);
        
    }while((fabs(U_p-Up_old))>eps);     //continues to calculate until I_p and I_R are not close to each other by less than Epsilon eps

    return U_p;
}

int main(int argc, char **argv){

    if(argc!=4){                        //programme has to have 3 arguments to run properly. 4 is 3 arguments + 1 for name of app
        Function_Error();
	return 1;
    }
    
    double u0=Convert(&argv[1]);        //have to convert argv strings to double numbers
    if(u0==1){
      return 1;
    }
    double r=Convert(&argv[2]);   
    if(r==1){
      return 1;
    }
    double eps=Convert(&argv[3]);
    if(eps==1){
      return 1;
    }
    
    //printf("%g %g %g",u0,r,eps);      debugging print

    double U_p=diode(u0, r, eps);
    
    fprintf(stdout,"Up=%g V \nIp=%g A\n",U_p,I_0*(exp((U_p/U_T))-1.));      //prints the results as is declared in assignment

    return 0;
}
