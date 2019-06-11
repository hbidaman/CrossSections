//#include "TROOT.h"
//#include "TLegend.h"
//#include "TGraphErrors.h"
//#include "TCanvas.h"
//#include "TMultigraph.h"
void multiplotzoomed() {


TCanvas *  myCanvas = new TCanvas("myCanvas", "multiple"); //can have ("myCanvas", "mulitplot", 0., 10.)
myCanvas->SetGrid(); //grid

TMultiGraph *  MG = new TMultiGraph();



TGraphErrors * graph1 = new TGraphErrors("CrossSectionsZoomed.txt", "%lg %lg %lg"); //X, Y, Yerr
//graph1->SetTitle("graph1");
graph1->SetMarkerStyle(24);
graph1->SetMarkerColor(kBlack);
graph1->SetLineColor(kBlack);
graph1->SetLineWidth(1);
graph1->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph1->GetYaxis()->SetTitle("Cross Section (barns)");
//graph1->Draw();
//MG->Add(graph1);

TGraphErrors * graph2 = new TGraphErrors("ElasticCrossSectionZoomed.txt", "%lg %lg %lg"); //X, Y, Yerr
//graph2->SetTitle("graph2");
graph2->SetMarkerStyle(25);
graph2->SetMarkerColor(kBlack);
graph2->SetLineColor(kBlack);
graph2->SetLineWidth(1);
graph2->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph2->GetYaxis()->SetTitle("Cross Section (barns)");
//graph2->Draw();

TGraphErrors * graph3 = new TGraphErrors("InElasticCrossSectionZoomed.txt", "%lg %lg %lg"); //X, Y, Yerr
graph3->SetMarkerStyle(26);
graph3->SetMarkerColor(kBlack);
graph3->SetLineColor(kBlack);
graph3->SetLineWidth(1);
graph3->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph3->GetYaxis()->SetTitle("Cross Section (barns)");

TGraphErrors * graph4 = new TGraphErrors("ENDFTotal.txt", "%lg %lg"); //X, Y
graph4->SetMarkerStyle(1);
graph4->SetMarkerColor(kRed);
graph4->SetLineColor(kRed);
graph4->SetLineWidth(11);
graph4->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph4->GetYaxis()->SetTitle("Cross Section (barns)");
MG->Add(graph4, "lp");

TGraphErrors *  graph5 = new TGraphErrors("ENDFElastic.txt", "%lg %lg"); //X, Y
graph5->SetMarkerStyle(1);
graph5->SetMarkerColor(kGreen);
graph5->SetLineColor(kGreen);
graph5->SetLineWidth(7);
graph5->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph5->GetYaxis()->SetTitle("Cross Section (barns)");
MG->Add(graph5, "lp");

auto graph6 = new TGraphErrors("ENDFInElastic.txt", "%lg %lg"); //X, Y
graph6->SetMarkerStyle(1);
graph6->SetMarkerColor(kBlue);
graph6->SetLineColor(kBlue);
graph6->SetLineWidth(3);
graph6->GetXaxis()->SetTitle("Excitation Energy (MeV)");
graph6->GetYaxis()->SetTitle("Cross Section (barns)");
MG->Add(graph6, "lp");

//MG->GetXaxis()->SetTitle("Excitation Energy (MeV)");
//MG->GetYaxis()->SetTitle("Cross Section (barns)");
MG->Add(graph2, "p");
MG->Add(graph1, "p");
MG->Add(graph3, "p");
MG->Draw("a");
//MG->Draw("alp");

//graph1->Draw();
MG->GetXaxis()->SetTitle("Excitation Energy (keV)");
MG->GetYaxis()->SetTitle("Cross Section (barns)");

auto legend = new TLegend(.7,.7,.9,.9); // still not quite sure how to position legend
legend->SetHeader("Title", "C");
legend->SetFillColor(0);
//MG->SetFillColor(0);
legend->AddEntry(graph1, "Simulated Total", "lep");
legend->AddEntry(graph2, "Simulated Elastic", "lep");
legend->AddEntry(graph3, "Simulated Inelastic", "lep");
legend->AddEntry(graph4, "ENDF Total", "l");
legend->AddEntry(graph5, "ENDF Elastic", "l");
legend->AddEntry(graph6, "ENDF NON", "l");
//legend->SetLegendTextSize(0.4);
//leg.DrawClone("Same");
//legend->Draw();
//myCanvas->BuildLegend();
 // MG->Draw("apl1");  
    myCanvas->Print("multizoomed.pdf");


}

int main() {
multiplotzoomed();
}

