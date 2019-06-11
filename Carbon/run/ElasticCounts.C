float CrossSection(double hits){

double TotalEvents = 50000.;
double eff =hits/TotalEvents;
float cross;
float u = 1.66053904e-24; //g
float massH = 1007825.03224e-6*u; //grams
//float massH = 1.6737e-24; //grams
//float density = 8.3748e-5; //g/cm^3
float MM = 12.0; // g/mol
float Na = 6.022e23; // 1/mol
float density = 12.0; //g/cm^3
double thickness = 1.0; //cm
//cross = -massH*log(1-eff)/(density*thickness)/10000*1e28; //m^2->barns
cross = -MM*log(1.-eff)/(density*thickness*Na)/10000*1e28; //m^2->barns
return cross;
}

double Errors(double error) {

double TotalEvents = 50000.;
double eff =error/TotalEvents;
float Error;
float u = 1.66053904e-24; //g
float massH = 1007825.03224e-6*u; //grams
//float massH = 1.6737e-24; //grams
//float density = 8.3748e-5; //g/cm^3
float MM = 12.0; // g/mol
float Na = 6.022e23; // 1/mol
float density = 12.0; //g/cm^3
double thickness = 1.0; //cm
float Der  = -MM/(density*thickness*Na*(error-TotalEvents))/10000*1e28; //m^2->barns
Error = sqrt(error) * Der;

return Error;

}

double ElasticCounts(float E) {

	
//Open File
TFile *f= TFile::Open("B1.root");
//Open B1 TTree
TTree * T = (TTree*)f->Get("B1");
//Draw histogram and create object h
T->Draw("Counts>>h1(1000., 0., 1000.)");
//Access h and integrate
TH1D * h1 = (TH1D*)gROOT->FindObject("h1");
//Draw histogram and create object h
T->Draw("ElCounts>>h(1000., 0., 1000.)");
//Access h and integrate
TH1D * h = (TH1D*)gROOT->FindObject("h");

double check = h1->Integral();
//ensure all hits are accounted for
if (check==50000.) {
double number = h->Integral(0., 1.);
double number1 = h1->Integral(0., 1.);
cout << number1 << endl;
double subtract1 = 50000. - number1;
double subtract = 50000. - number;
cout << subtract << endl;
double energy = E*1E6; // MeV

float CROSS = subtract*CrossSection(subtract1)/subtract1;
cout<< CROSS << endl;
float ERROR = subtract*Errors(subtract1)/subtract1;
//Write to file
FILE *F2;
F2 = fopen("ElasticCrossSection.txt", "a");
fprintf(F2, "%lf\t%lf\t%lf\n", energy, CROSS, ERROR);
//fprintf(F2, "%lf\t%lf\t%lf\n", time, run, number);
fclose(F2);

}

else {
cout << "Dont have all counts" << endl;
}
return 0;
}
