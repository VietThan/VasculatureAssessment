I = niftiread('volume_norm_tif_Hessian_0p8_1p0_250p0_2p0_11p0_10.nii');
% has to be odd 
T = adaptthresh(I, 0.00001, 'NeighborhoodSize', [3 3 3]);
BW = imbinarize(I, T);
BW = single(BW);
niftiwrite(BW, 'outBinarize_0p00001_3.nii');
