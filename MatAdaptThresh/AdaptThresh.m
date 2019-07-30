I = niftiread('volume_norm_tif_Hessian_0p8_1p0_250p0_2p0_11p0_10.nii');
% has to be odd 
T = adaptthresh(I, 0.001, 'NeighborhoodSize', [1 1 1]);
BW = imbinarize(I, T);
BW = single(BW);
niftiwrite(BW, 'outBinarize_0p001_1.nii');
