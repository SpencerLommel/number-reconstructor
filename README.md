# Number Reconstructor

This program uses the [BMP Parser](https://github.com/SpencerLommel/spencer-bmp) I wrote a few months ago to reconstruct training data from the MNIST Dataset to a BMP image. 

The dataset I'm starting with consists of 785 columns, the first column is the actual value of the number and the last 784 is each pixel in a 28x28 grid.

So esentially we start with a CSV of a bunch of pixels and we construct it into an actual image!

# What is the MNIST dataset?
The MNIST (Modified National Institute of Standards and Technology database) is a database of handwritten digits that is mostly used for image processing and machine learning. 

# Why reconstruct them?
 I'm experimenting with writing machine learning models in C to target embedded devices (mostly microcontrollers) with the end goal of training and running an AI model to detect a hand written number completely on a microcontroller!

 # Usage

So far I've just made a simple program to generate a bmp from the csv data and you can test it like this.
```
make
./build/reconstruct-number
```

And then you will get something like this!