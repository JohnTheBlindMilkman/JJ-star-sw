// $Id: TpcResponseSimulator.y2020.C,v 1.1 2021/05/10 21:02:56 fisyak Exp $
// $Log: TpcResponseSimulator.y2020.C,v $
// Revision 1.1  2021/05/10 21:02:56  fisyak
// Clean up and synch with TFG
//
// Revision 1.4  2020/04/03 23:47:14  fisyak
// rename tpcSectorT0offset.20190223.080000.C to tpcSectorT0offset.20190101.000000.C, remove intermidiate tpcSectorT0offset.20190*.C
//
// Revision 1.3  2019/05/23 11:50:01  fisyak
// Add default TpcAdcCorrectionMDF, 2019 version of TpcResponseSimulator
//
// Revision 1.2  2019/04/16 19:29:34  fisyak
// Run XIX preliminary dE/dx calibration
//
// Revision 1.1  2018/02/16 20:56:50  perev
// iTPC
//
// Revision 1.1  2017/02/07 16:58:36  fisyak
// Clean up
//
// Revision 1.1  2012/09/13 21:06:27  fisyak
// Default tables for devT
//
// Revision 1.1  2012/04/27 00:31:31  perev
// All defE tables
//
// Revision 1.8  2012/04/11 14:21:55  fisyak
// Fix T0offset from comparison with AuAu27
//
// Revision 1.7  2012/04/03 14:06:55  fisyak
// Speed up using  GetSaveL (__PAD_BLOCK__), sluggish shape histograms, Heed electron generation
//
// Revision 1.6  2012/01/18 13:57:57  fisyak
// Adjust T0offset : Xianglei Zhu from Run 11 AuAu 27 & 19.6 GeV embedding
//
// Revision 1.5  2011/12/30 00:04:01  fisyak
// Freeze parameters for y2011 base on TpcRS_2011_pp500LowLum_Q
//
// Revision 1.3  2011/10/11 19:09:23  fisyak
// Add Yi Guo's tables for Run XI AuAu200 RFF dE/dx calibration
//
// Revision 1.2  2010/10/28 23:41:54  fisyak
// extra t0 off set for Altro chip
//
// Revision 1.7  2010/06/14 23:36:08  fisyak
// Freeze version V
//
// Revision 1.6  2010/05/24 21:39:53  fisyak
// Fix bracket
//
// Revision 1.5  2010/05/24 16:07:20  fisyak
// Add default dE/dx calibration tables, replace TpcAltroParameters and asic_thresholds_tpx by tpcAltroParams
//
// Revision 1.4  2010/04/19 15:05:58  fisyak
// Final (2010_i) parameters for Run X
//
// Revision 1.3  2010/04/16 19:31:19  fisyak
// Intermidiate version
//
// Revision 1.3  2010/04/04 23:14:33  fisyak
// Add Row Correction
//
// Revision 1.2  2010/04/01 22:17:57  fisyak
// Freeze version W
//
TDataSet *CreateTable() { 
  // -----------------------------------------------------------------
  // db/.const/StarDb/Calibrations/tpc/.TpcResponseSimulator/TpcResponseSimulator Allocated rows: 1  Used rows: 1  Row size: 124 bytes
  //  Table: TpcResponseSimulator_st[0]--> TpcResponseSimulator_st[0]
  // ====================================================================
  // ------  Test whether this table share library was loaded ------
  if (!TClass::GetClass("St_TpcResponseSimulator")) return 0;
  TpcResponseSimulator_st row;
  St_TpcResponseSimulator *tableSet = new St_TpcResponseSimulator("TpcResponseSimulator",1);
  memset(&row,0,tableSet->GetRowSize());
  row.I0                    = 13.1;// eV, CH4 		       
  row.Cluster    	    = 3.2; // average no. of electrons per primary  			       
  row.W          	    = 26.2;// eV 								       
  row.OmegaTau   	    = 3.02;// fit of data 							       
  row.K3IP       	    = 0.68;//(pads) for a/s = 2.5e-3 and h/s = 0.5 
  row.K3IR       	    = 0.89;//(row)  for a/s = 2.5e-3 and h/s = 0.5 
  row.K3OP       	    = 0.55;//(pads) for a/s = 2.5e-3 and h/s = 1.0 
  row.K3OR       	    = 0.61;//(row)  for a/s = 2.5e-3 and h/s = 1.0 
  row.FanoFactor 	    = 0.3; //                                                                        
  row.AveragePedestal       = 50.0;// 
  row.AveragePedestalRMS    = 1.0; // Old Tpc electronics or iTPC  1.4 => 1.0; Tonko 12/12/2019
  row.AveragePedestalRMSX   = 0.7; // New Tpx electronics 
  row.tauIntegration        = 2.5*74.6e-9;//   secs 
  row.tauF                  = 394.0e-9;// secs Tpc 
  row.tauP                  = 775.0e-9;// secs Tpc 
  row.tauXI                 =  60.0e-9;// secs Tpx Inner integration time 
  row.tauXO                 =  74.6e-9;// secs Tpx Outer integration time 
  row.tauCI                 =   0;  
  row.tauCO                 =   0;  
  row.SigmaJitterTI         = 0.4317/4.5;// 0.4317;// 0.25;//ad  0.0;// b for Tpx inner 
  row.SigmaJitterTO         = 0.4300/5.;// 0.4300;// E: 0.4801;//0.25;//ad  0.0;// b for Tpx outer 
  row.SigmaJitterXI         = 0.1027785/2.;// 0.1027785; // P: 0.1353*1.05/1.10; //O: 0.1353*1.05;// N: 0.1353; // C:0.;
  row.SigmaJitterXO         = 0.107525/2.; // 0.107525;  // P: 0.1472*1.05/1.03; //O: 0.1472*1.05;// N: 0.1472; // C:0.;
  row.longitudinalDiffusion = 0.03624; // Magboltz // HD 0.03624*1.5; //HC 0.03624; // Magboltz 
  row.longitudinalDiffusionI= row.longitudinalDiffusion;
  row.transverseDiffusion   = 0.02218*TMath::Sqrt(1 + row.OmegaTau*row.OmegaTau) ; // Magboltz
  row.transverseDiffusionI  = 0.83* row.transverseDiffusion;
  row.NoElPerAdc            = 335.;   // No. of electrons per 1 ADC count
  row.OmegaTauScaleI        =  2.145*1.515;// HC 1.;// 2.145*1.515;  //i; 2.145*1.4;  //h 2.145;  //ad 2.145*1.25;  //b effective reduction of OmegaTau near Inner sector anode wire
  row.OmegaTauScaleO        = 1.8  *1.201;  //HC 1.;// 1.8  *1.201;  //i 1.8  *1.1;    //h 1.8;    //ad 1.8  *1.25;  //b effective reduction of OmegaTau near Outer sector anode wire
if 0
  // Inner_wire_to_plane_coupling ( 0.533 ) * Inner_wire_to_plane_couplingScale ( 0.843485 )
  // Outer_wire_to_plane_coupling ( 0.512 ) * Outer_wire_to_plane_couplingScale ( 0.725267 )
  row.SecRowCorIW[0] = row.SecRowCorIE[0] = 6.99114715017355337e-01 +1.14433e-01 -3.57593e-01 -3.95075e-02 -2.12902e-02 -2.43764e-03 +1.92592e-01; // hijingAuAu200.DEV2X5.StiCA.Minuit
  row.SecRowCorOW[0] = row.SecRowCorOE[0] = 9.79357470004933006e-01 -6.15827e-02 +1.99821e-01              +6.06971e-03 -6.98644e-04 -1.37937e-01;
#endif
  const Float_t RowMuTrs[8] = {
    8.58173375017355466e-01,  -5.31599e-03,
    9.59121536004932995e-01,   2.01122e-03,
    6.99268875017355351e-01,  -4.17326e-03,
    9.57378636004933004e-01,   2.02957e-03
  };
  Float_t *a = &row.SecRowCorIW[0];
  for (Int_t i = 0; i < 8; i++) {
    a[i] = RowMuTrs[i%4];
  }
#if 0
  // SecRow3CGFdaq_2011_pp500LowLum => Inner: 3.26428e-01 - -5.01720e-04*y; Outer: 2.68883e-01 + 1.23403e-04*y
  //                                          3.22907e-01                          2.72715e-01
  // SecRow3CGFTpcRS_2011_pp500LowLum_f     : 3.09711e-01                          2.65342e-01
  // diff                                   : 9.13675e-02                          6.29849e-02
  // SecRow3CGFTpcRS_2011_pp500LowLum_g     : 3.12857e-01                          2.67379e-01
  const Double_t RowSigmaTrs[4] = {
    0.2313675,   0,  // 9.13675e-02, 0,  // Inner // 9.13675e-02+0.14
    6.29849e-02, 0}; // Outer
  Float_t *b = &row.SecRowSigIW[0];
  for (Int_t i = 0; i < 8; i++) {
    b[i] = RowSigmaTrs[i%4];
  }
#endif
  row.PolyaInner = 1.38;
  row.PolyaOuter = 1.38;
  //  row.T0offset   = 0.50; // From  Lokesh Kumar for Run X
  // TpcT->Draw("fMcHit.mMcl_t+0.165*Frequency-fRcHit.mMcl_t/64:fMcHit.mPosition.mX3>>T(210,-210,210,100,-2,3)","fNoMcHit==1&&fNoRcHit==1&&fRcHit.mQuality>90","colz")
  // TpcT->Draw("fMcHit.mPosition.mX3-fRcHit.mPosition.mX3:fMcHit.mPosition.mX3>>Z(210,-210,210,100,-2,3)","fNoMcHit==1&&fNoRcHit==1&&fRcHit.mQuality>90","colz")
  // The corection has to be added                                                                    M             P
  //row.T0offset   = 0.50 + 1.65431e-01 -  3.45247e-01 -1.54583e+00 -2.90686e-03+ 1.54353e+00 + 0.0191135  -1.20938e-03 ; //E
  // row.T0offset   = 0.50 -1.43663e-01 -0.00932877;//g // 01/18/12 Xianglei Zhu from Run 11 AuAu 27 & 19.6 GeV embedding 
  row.T0offset   = 0.50 -1.43663e-01 -0.00932877 + 0.0416 -0.053;//2020 AuAu11p5
  /* 
     0.05  => -0.154  
    -0.05  => -0.054
    -0.104 => -0.006  but very big sigma 0.298 => 0.303 
    row.FirstRowC  = -0.104;  // extra correction for pad row 1 due to disabled firth 3 anode wires, check with X7
    No. cut on 3 first wires => -9.21881e-02 ; X9
    row.FirstRowC  = -0.104;  // extra correction for pad row 1 due to disabled firth 3 anode wires
   */
  row.RecombinationI =  row.RecombinationO = 2;
  row.Sigma_xWI = row.Sigma_xWO = row.Slope_zWI = row.Slope_zWO = 0.0100; 
  tableSet->AddAt(&row);
  // ----------------- end of code ---------------
  return (TDataSet *)tableSet;
}
