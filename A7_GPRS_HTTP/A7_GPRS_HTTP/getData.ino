void getData(Data* data){
	Serial.println(F("Hello I am getting your DATA!!! :)"));
	int Navg =800 ;
	uint16_t datatemperature = 0;
	uint16_t datapH = 0;
	uint16_t dataDO = 0;
	int dataturbidity = 0;

	for(int i=0; i<Navg; i++){
	 datatemperature += analogRead(pinTemperature);
	 datapH += analogRead(pinPH);
	 dataturbidity += analogRead(pinTurbidity);
	}
	datatemperature = datatemperature/Navg;
	datapH = datapH/Navg;
	dataDO = dataDO/Navg;
	dataturbidity = dataturbidity/Navg;

	if( dataturbidity >= 1023) {
		dataturbidity = 1023;
		}

	data->pH = (datapH*(5.0/1023.0)-0.88)/3.52*14.00;
	if (data->pH <0) data->pH = 0;

	data->DO = (dataDO*(5.0/1023.0)-0.88)/3.52*100.00;
	if (data->DO <0) data->DO = 0;

	data->temperature = ((datatemperature*(5.0/1023.0)-0.88)-1.76)/1.76*50;

	data->turbidity = (dataturbidity*-5.69) + 4000;
	if (data->turbidity <0) data->turbidity = 0;
}

void printData(Data* data){
	Serial.print(F("Temperature is: "));
	Serial.println(data->temperature);
	Serial.print(F("pH is: "));
	Serial.println(data->pH);
	Serial.print(F("DO is: "));
	Serial.println(data->DO);
	Serial.print(F("Turbidity is: "));
	Serial.println(data->turbidity);
}
