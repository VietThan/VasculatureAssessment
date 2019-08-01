name = sprintf('volume_norm_tif_Hessian_0p001_1p0_1p0_2p0_6p0_9');
inputName = append(name, sprintf('.nii'));
outputName = append(sprintf('Adapt5_'), name, sprintf('.nii'));
disp(['Input: ' inputName]);
disp(['Output: ' outputName]);

I = niftiread(inputName);
disp('File read');

% has to be odd 
T = adaptthresh(I, 0.01, 'NeighborhoodSize', [5 5 5]);
disp('Threshold evaluated');

BW = imbinarize(I, T);
BW = single(BW);
disp('Binarized');

niftiwrite(BW, outputName);
disp('File written out');