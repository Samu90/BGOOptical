{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile* f = TFile::Open("CherV6.root");  
  TCanvas* c1 = new TCanvas("c1", "  ", 600, 600);
  
  TDirectory* dir = (TDirectory*)f->Get("histo");

  TStyle* style = new TStyle("DrawBaseStyle", "");
  style->SetCanvasColor(0);
  style->SetPadColor(0);
  style->SetFrameFillColor(0);
  style->SetStatColor(0);
  style->SetOptStat(0);
  style->SetOptFit(0);
  style->SetTitleFillColor(0);
  style->SetCanvasBorderMode(0);
  style->SetPadBorderMode(0);
  style->SetFrameBorderMode(0);
  style->SetPadBottomMargin(0.12);
  style->SetPadLeftMargin(0.12);
  style->cd();

  
  TH1D* hist1 = (TH1D*)dir->Get("Edep1");      
  hist1->Draw("HIST");
  hist1->SetLineWidth(2);
  hist1->SetLineColor(3);
  //hist1->Rebin(2);

  hist1->SetXTitle("Energia [MeV]");


  TH1D* hist2 = (TH1D*)dir->Get("Edep2");      
  hist2->SetLineColor(kRed);
  hist2->SetLineWidth(2);
  hist2->Draw("HIST same");
  //  hist2->Rebin(2);
  //TCanvas* c2 = new TCanvas("c2", " ", 600,600);  
  TH1D* hist3 = (TH1D*)dir->Get("Edep3");      
  hist3->SetLineColor(kBlue);
  hist3->SetLineWidth(2);
  hist3->Draw("HIST same");

  //  TLegend* legend = new TLegend(...);

  c1->SaveAs("plot.pdf");
  c1->SaveAs("plot.png");

}
