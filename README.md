# Scripts for quantitative assesment of (retinal) microvasculature<br>

<p align="center"><img src="https://www.spiedigitallibrary.org/ContentImages/Journals/JBOPFO/21/6/066008/FigureImages/JBO_21_6_066008_f002.png" width=500></p>

<p align="left">
	<img src="https://img.shields.io/badge/platform-ubuntu-blueviolet?style=for-the-badge"
			 alt="platform">
	<img src="https://img.shields.io/badge/language-C++11-green?style=for-the-badge"
			 alt="language">
  	<img src="https://img.shields.io/badge/compiler-GCC 5.4.0-green?style=for-the-badge"
			 alt="compiler">
	<img src="https://img.shields.io/badge/builder-cmake 3.7.1-green?style=for-the-badge"
			 alt="builder">
	<img src="https://img.shields.io/badge/library-ITK 4.12.2|Python2.7.12-critical?style=for-the-badge"
			 alt="compiler">
</p>

## General Information<br>
### Theoretical foundation<br>
These scripts are based on the descriptions from the following paper:<br>
"Quantitative assessment of the retinal microvasculature using optical coherence tomography angiography". Journal of Biomedial Optics, 21(6), 066008. 2016. Zhongdi Chu; Jason Lin; Chen Gao; Chen Xin; Qinqin Zhang; Chieh-Li Chen; Luis Roisman; Giovanni Gregori; Philip J. Rosenfeld; Ruikang K. Wang<br>
<a href="https://www.spiedigitallibrary.org/journals/Journal-of-Biomedical-Optics/volume-21/issue-6/066008/Quantitative-assessment-of-the-retinal-microvasculature-using-optical-coherence-tomography/10.1117/1.JBO.21.6.066008.full?SSO=1&tab=ArticleLink">Link to paper</a>
### Useful information about ITK<br>
Dimensions {x, y. z} corresponds to [0], [1], [2] when workin with ITK arrays that uses those dimensions/directions (index, size etc.)<br>
Read more about ITK at <a href="https://itk.org/">itk.org</a>
### Useful information about styles
* For input, `type` means the file type associated with `filename`.
* The scrips make output filenames themselves by using the input filename and append useful information about what happened.
* If the program runs with more arguments than specified, the program will `EXIT_FAILURE`. 
* If the program runs with less arguments than specified, default arguments will be ran.

## Scripts

### AdaptiveThreshold

Complete/Abandoned. Implementing adaptive threshold filter. Abandoned because underlying filter is deprecated and suspect not implementing adaptive threshold correctly

### WhiteHatThreshold

Complete/Abandoned. Implementing the white hat filter, bringing out local maxima of bright objects on dark background. The filter isn't working correctly, output remained the same as input.<br>

Arguments: ```./WhiteHatThreshold [filename] [filetype] [algorithm] [radius]```

Default:   ```./WhiteHatThreshold volume_norm_tif .nii 0 8```

### MatAdaptThresh
Complete. Micro script on MATLAB to make use of its adaptive thresholding and image binarizing functions. Playing around with parameters currently gives neighborhood sizes of [1 1 1] very effective.<br><br>
Arguments: No arguments

## More

## Author and Acknowledgements
Author: Viet Than, Department of EECS, Vanderbilt University, US.
Supervisor: Ipek Oguz, Prof. Department of EECS, Vanderbilt University, US.

With the help of the Medical Image Computing Lab.
