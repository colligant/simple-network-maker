# Simple language to generate fully connected networks
Use the makefile to compile the code. Development was done on a mac.
use the software as follows: ./graph.out

Define a fully-connected layer like this:
```
a=[n_nodes]
```
where n_nodes is a positive integer. In the example above, a is the layer name.
Successive layers can be added by just calling the function above multiple times.
![network made with this software](test.pdf) by using the following commands:
```
input=[28]
hidden1=[10]
hidden2=[10]
output=[2]
print
```
Issuing the print command writes the generated dot code to a file, named graph.dot.out.
To view the graph, type this into the terminal (assuming dot is installed)
```
dot -Tpdf graph.dot.out -o out.pdf
```
