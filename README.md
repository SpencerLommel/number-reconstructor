# Number Reconstructor

This program uses the [BMP Parser](https://github.com/SpencerLommel/spencer-bmp) I wrote a few months ago to reconstruct training data from the MNIST Dataset to a BMP image. 

The dataset I'm starting with consists of 785 columns, the first column is the actual value of the number and the last 784 is each pixel in a 28x28 grid.

So esentially we start with a CSV of a bunch of pixels and we construct it into an actual image!

# What is the MNIST dataset?
The MNIST (Modified National Institute of Standards and Technology database) is a database of handwritten digits that is mostly used for image processing and machine learning. 

# Why reconstruct them?
 I'm experimenting with writing machine learning models in C to target embedded devices (mostly microcontrollers) with the end goal of training and running an AI model to detect a hand written number completely on a microcontroller!

 # Usage

There is either a `demo` program which just generates `4.bmp` or `line-number` which allows you to specify a certain row in the testing data to generate.

`line-number` is mostly used for me to validate the accuracy of my model and help with tweaking my weights

First unzip the `mnist-in-csv.zip` to a folder called `mnist-in-csv` and then make and run the program
```
make
./build/demo
```

And then you will get something like this!

![Hand written number 4](/docs/4.bmp)


You can also run `line-number` like this:
```
spencer@spencer-thinkpad:~/Documents/code/C/number-reconstructor$ ./build/line-number 
Usage: ./build/line-number <row_number>
spencer@spencer-thinkpad:~/Documents/code/C/number-reconstructor$ ./build/line-number 1
Row number must be 2 or more (row 1 is header)
spencer@spencer-thinkpad:~/Documents/code/C/number-reconstructor$ ./build/line-number 40
Generated BMP for row 40 with number 2
spencer@spencer-thinkpad:~/Documents/code/C/number-reconstructor$ 
```

and here's our result!

![Hand written number 2](/docs/2.bmp)

