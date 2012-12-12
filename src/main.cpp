int main(int argc, char** argv)
{


	std::string msgPhins = "PIXSE,CONFIG,RSOUTA,4,1,1000,0,0,1,0*"; // Phins Standard , 1Hz
	std::string msgHalli = "PIXSE,CONFIG,RSOUTA,4,3,500,0,0,1,0*"; // Halliburton , 2Hz
	std::string msgHeading = "PIXSE,CONFIG,RSOUTA,4,13,1000,0,0,1,0*"; // HEHDT, 1 Hz

	std::cout<<"main"<<std::endl;


 	Driver *d = new Driver(PhinsStandard );

 	std::cout<<"ready"<<std::endl;
 	d->open(PORT_PHINS);
	int i = 0;
	while( i++ < 10){
		//std::cout<<"loop"<<std::endl;
		d->read(2000);
		 //testRBS = d->getRBS();
		 //std::cout<< "test rbs x " << testRBS.position.x()<< std::endl;
		 // std::cout<< "test rbs y" << testRBS.position.y()<< std::endl;
	}

	std::cout<<"reboot tut gut.."<<std::endl;
	d->resetPhins();
	std::cout<<" ..ready "<<std::endl;
	i = 0;

	while( i++ < 10){
		std::cout<<" again "<<std::endl;
			d->read(2000);
	}



	delete d;

	return 0;
}
