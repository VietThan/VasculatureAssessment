# Scripts for quantitative assesment of (retinal) microvasculature<br>
## General Information<br>
### Theoretical foundation<br>
These scripts are based on the descriptions from the following paper:<br>
"Quantitative assessment of the retinal microvasculature using optical coherence tomography angiography". Journal of Biomedial Optics, 21(6), 066008. 2016. Zhongdi Chu; Jason Lin; Chen Gao; Chen Xin; Qinqin Zhang; Chieh-Li Chen; Luis Roisman; Giovanni Gregori; Philip J. Rosenfeld; Ruikang K. Wang<br>
### Useful information about ITK<br>
Dimensions {x, y. z} corresponds to [0], [1], [2] when workin with ITK arrays that uses those dimensions/directions (index, size etc.)<br>
Read more about ITK at <a href="https://itk.org/">itk.org</a>
### Useful information about styles
For input, when I use `type`, it means the file type associated with `filename`. This was used for ease of access and making output file name. In theory, every script will append useful information about what happened and as such based the output filename  on `filename`.<br>
If the program runs with more arguments than specified, the program will `EXIT_FAILURE`. If the program runs with less arguments than specified, default arguments will be ran.<br> 
## Scripts<br>
### AdaptiveThreshold<br>
Complete/Abandoned. Implementing adaptive threshold filter. Abandoned because underlying filter is deprecated and suspect not implementing adaptive threshold correctly<br>
### WhiteHatThreshold<br>
Complete. Implementing the white hat filter, bringing out local maxima of bright objects on dark background<br>
>Arguments:<br>
>`./WhiteHatThreshold [filename] [filetype] [algorithm] [radius]`<br>
>Default:<br>
>`./WhiteHatThreshold volume_norm_tif .nii 0 8`<br>
## More<br>

