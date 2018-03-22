To start with this project, you can do 
1. gcc -o airlinereservation airlinereservation.c airplane.c -pthread
or 2. do make 

Then it will make an executable called airlinereservation

To execute the file, 
type ./airlinereservation 5 out.txt
in which 5 is the number of customers, out.txt is the outputFile name

Note: the outputs will not be in orders since children are in parallel process
Each customers can book the plane more than once. 

The sample out.txt is ran as a result of having 5 customers
the out3.txt is a result of having 3 customers
the out8.txt is result of having 8 customers
