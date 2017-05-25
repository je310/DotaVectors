# Vector tutorial. 

The purpose of this code is to demonstrate some of the reasons you might want to use a vector in you code. Read through the code paying attention to the comments. It is not neccessary for you to understand every line of code at first. After looking through the code you can uncomment the lines that reveal fun answers to difficult questions in Dota. With each new question I increase the complexity of the code, so try and see what variables are doing what in the code before moving on.

For a basic introduction to vectors visit this site https://medium.com/the-renaissance-developer/c-standard-template-library-stl-vector-a-pretty-simple-guide-d2b64184d50b it talks in fairly simple terms about what a vector is. 

The main thing is to have fun and don't get fustrated with any of the code, I wanted to make the questions exciting. Try adding breakpoints in the code (if you get it working within XCode) and see what the variables are doing that way. 

#To run the code: 
In a folder of your choosing run: 
git clone https://github.com/je310/DotaVectors.git 

You can then open this in Xcode (though I have no particular way to help you set that up as I do not use it myself. A hack would be to copy and pase the contents of main.cpp and dotaStats.csv to the equivelent files in your current project.). 
or you can compile by doing the following. 

(inside the cloned directory) 

mkdir build 

cd build 

cmake ..

make 

./dota_code 


To recompile after editing main.cpp you only need to do "make", whilst in the build directory to recompile.  

#(explanation of the above for reference) 

mkdir build (make a new directory called build, this is where all generated files will end up) 

cd build (change directory to the newly created biuld directory) 

cmake ..  (Run cmake in the folder 'one up' from here, cmake is program that sets up your compilation system according to the information I have saved in the CMakeLists.txt file.) 

make (run the compiler with the settings we just got cmake to prepare for us) 

./dota_code (run the code !). 
