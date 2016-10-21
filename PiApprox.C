#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TCanvas.h>
#include <Riostream.h>
#include <TFile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TMath.h>
#endif

void Pi(Int_t Try = 1000, const UInt_t seed = 123){
  
  const int MAX = 2000; 
  int InCircle = 0;
  const double side = 2.; 
  double randx,randy;
  double p = 0.;

  char title[50];
  char canvas_name[50];

  TH2D *h[3] = {0};
  TCanvas *c[3];    
  
  if(Try < 1){
    cout << "Tries' number must be > 0  ------>  default Try: 10000" << endl;
    Try = 1000;
    cout << endl;
  }

  for(int mcn = 0; mcn < 3; mcn++){

    c[mcn] = new TCanvas();
    sprintf(title, "Number of tries: %d", Try);
    h[mcn] = new TH2D("Data", title, 100, -1, 1, 100, -1, 1);
	 
    if(mcn == 0){
      sprintf(canvas_name, "Pi canvas -> Square");
      c[mcn] -> SetTitle(canvas_name);}
    
    if(mcn == 1){
      sprintf(canvas_name, "Pi canvas -> Circle");
      c[mcn] -> SetTitle(canvas_name);}

    if(mcn == 2){
      sprintf(canvas_name, "Pi canvas -> Random fill");
      c[mcn] -> SetTitle(canvas_name);}
  }

  if(Try < MAX)
    cout << "\n----------" << endl;
  else
    cout<<endl;
  
  for (Int_t i = 1; i <= Try; i++)
    {
      randx = gRandom -> Uniform(-1, 1);
      randy = gRandom -> Uniform(-1, 1);    
     
      for(int mcn = 0; mcn < 3; mcn++){
	
	if(mcn == 0){
	  h[mcn] -> Fill(randx, randy, 1);
	}
	
	if(mcn == 1){
	  if( (randx*randx) + (randy*randy) <= side/2*side/2 ){
	    InCircle += 1.;
	    h[mcn] -> Fill(randx, randy, 1);}
	}

	if(mcn == 2){
	  h[mcn] -> Fill(randx, randy, 1);
	}
      }

      for(int j = 0; j <= Try; j += 100)
	if(i == j && Try <= 1000){
          p = 4*(double)InCircle/Try;
	  cout << "Number " << i << ") Pi: " << p << endl;
	}
      
      if(Try <= MAX){
	gStyle -> SetPalette(55);
	c[2] -> cd();
	h[2] -> Draw("COLZ");
	c[2] -> Modified();
	c[2] -> Update();
      }      
    }

  p = 4*(double)InCircle/Try;
  cout << "----------\nBest Pi approximation: " << p << "\n----------\n" << endl;
  
  for(int mcn = 0; mcn < 3; mcn++){
    
    if(mcn == 0){
      c[mcn] -> cd();
      gStyle -> SetPalette(55);
      h[mcn] -> Draw("COLZ");}

     if(mcn == 1){
      c[mcn] -> cd();
      gStyle -> SetPalette(55);
      h[mcn] -> Draw("COLZ");}    
  

     if (mcn == 2){
       c[mcn] -> cd();
       gStyle->SetPalette(55);
       h[mcn] -> Draw("COLZ");}
  }
}
