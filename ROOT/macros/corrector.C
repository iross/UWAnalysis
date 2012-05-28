void corrector(float dataDenom,float dataDenomErr, float dataNum, float dataNumErr,float mcDenom,float mcDenomErr, float mcNum, float mcNumErr) {

  float correction = dataNum*mcDenom/(mcNum*dataDenom);
  float err = correction*sqrt( pow(mcNumErr/mcNum,2) +
			       pow(mcDenomErr/mcDenom,2)+
			       pow(dataNumErr/dataNum,2)+
			       pow(dataDenomErr/dataDenom,2));

  printf("Correction factor = %f +- %f \n",correction,err);
  

}
 
