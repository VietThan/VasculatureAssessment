I = niftiread('volume_norm_tif_Hessian_0p8_1p0_250p0_2p0_11p0_10.nii');
A = adaptthresh(I, 0.001, 'NeighborhoodSize', [5 5 5]);
B = rescale(A, 0, 255);
B = single(B);
niftiwrite(B, 'out.nii');
