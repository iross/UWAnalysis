float ratio(float a,float b,float da,float db) {

  printf("Result = %f +- %f\n",a/b,(a/b)*sqrt(da*da/(a*a) +db*db/(b*b)));

}

float product(float a,float b,float da,float db) {

  printf("Result = %f +- %f\n",a*b,(a*b)*sqrt(da*da/(a*a) +db*db/(b*b)));

}
