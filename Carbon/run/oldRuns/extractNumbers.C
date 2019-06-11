float CrossSection(double hits){

double TotalEvents = 50000.;
double eff =hits/TotalEvents;
float cross;
float u = 1.66053904e-24; //g
float massH = 1007825.03224e-6*u; //grams
//float massH = 1.6737e-24; //grams
float density = 8.3748e-5; //g/cm^3
double thickness = 1.0; //cm
cross = -massH*log(1-eff)/(density*thickness)/10000*1e28; //m^2->barns
return cross;
}

float Error(double error) {

	return 0;
}

double extractNumbers(float E) {

	
//Open File
TFile *f= TFile::Open("B1.root");
//Open B1 TTree
TTree * T = (TTree*)f->Get("B1");
//Draw histogram and create object h
T->Draw("Counts>>h(1000., 0., 1000.)");
//Access h and integrate
TH1D * h = (TH1D*)gROOT->FindObject("h");

double check = h->Integral();
//ensure all hits are accounted for
if (check==50000.) {

double number = h->Integral(0., 1.);
cout << number << endl;
double subtract = 50000. - number;
cout << subtract << endl;
double energy = E; // MeV

float CROSS = CrossSection(subtract);
cout<< CROSS << endl;
//Write to file
FILE *F2;
F2 = fopen("CrossSections.txt", "a");
fprintf(F2, "%lf\t%lf\n", energy, CROSS);
//fprintf(F2, "%lf\t%lf\t%lf\n", time, run, number);
fclose(F2);

}

else {
cout << "Dont have all counts" << endl;
}
return 0;
}
