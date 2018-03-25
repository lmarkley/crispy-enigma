#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef struct { float x,y,z; int idx; } vector4;

#define RAND_IN( min,max ) ((min) + (float)((max) - (min)) * rand() / RAND_MAX) // PRNG macro on the CPU

const float bond_length = 1.42;

void help_message()
{
	printf("Proper usage: \n");
	printf("u..........Creates uniform linear chain.\n");
	printf("n..........Creates non-uniform linear chain. \n");
	printf("h..........Displays this message. \n");
	printf("v [wire length] [bacteria length]..........Creates single chain with user specified wire and bacteria size.\n");
	printf("um, nm, vm [wire length] [bacteria length]..........Creates multiple chains of the specified type.\n");
	printf("r [number of wires]..........Creates a random layout with the supplied number of wires.\n");
}

void uniform_linear( int num_wires = 1 )
{
	printf("You have selected a uniform linear output! \n");

	vector4 atom[1000];
	vector4 orientation[1000];

	FILE *wire_data = fopen("center_data.dat","w");
	FILE *left_data = fopen("left_data.dat","w");
	FILE *right_data = fopen("right_data.dat","w");

	int index = 1;

	for ( int wire = 0; wire < num_wires; wire++ )
	{
		int chain_idx = 0;
		for ( int n = wire * 30; n < 30 + wire * 30; n++ )
		{
			atom[n].x = wire * bond_length;
			atom[n].y = 0.0;
			atom[n].z = chain_idx * bond_length;
			atom[n].idx = index;
			orientation[n].x = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].y = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].z = RAND_IN(-0.2,0.2);
			orientation[n].idx = index;
			chain_idx++;
		}
	}
		
	fprintf( left_data, "%i    %2.4f\n", 5 * num_wires, atom[29].z + bond_length );		
	fprintf( wire_data, "%i    %2.4f\n", 20 * num_wires, atom[29].z + bond_length );
	fprintf( right_data, "%i    %2.4f\n", 5 * num_wires, atom[29].z + bond_length );
	for (int wire = 0; wire < num_wires; wire++ )
	{
		for ( int i = wire * 30; i < 5 + wire * 30; i++ )
		{
			fprintf(left_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(left_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}

		for ( int i = 5 + wire * 30; i < 25 + wire * 30; i++ )
		{
			fprintf(wire_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(wire_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x, orientation[i].y, orientation[i].z);
		}	

		for ( int i = 25 + wire * 30; i < 30 + wire * 30; i++ )
		{
			fprintf(right_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(right_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}
	}
	

	printf("Finished writing data. \n");

	fclose(wire_data);
	fclose(left_data);
	fclose(right_data);
}

void nonuniform_linear( int num_wires = 1 )
{
	printf("You have selected a non-uniform linear output! \n");

	vector4 atom[1000];
	vector4 orientation[1000];

	FILE *wire_data = fopen("center_data.dat","w");
	FILE *left_data = fopen("left_data.dat","w");
	FILE *right_data = fopen("right_data.dat","w");

	int index = 1;

	for ( int wire = 0; wire < num_wires; wire++ )
	{
		int chain_idx = 0;
		for ( int n = wire * 30; n < 30 + wire * 30; n++ )
		{
			if ( n >= wire * 30 && n < 5 + wire * 30)
			{
				index = 1;
			}
			else if ( n >= 5 + wire * 30 && n < 10 + wire * 30 )
			{
				index = 2;
			}
			else if ( n >= 10 + wire * 30 && n < 15 + wire * 30 )
			{
				index = 1;
			}
			else if ( n >= 15 + wire * 30 && n < 20 + wire * 30 )
			{
				index = 2;
			}
			else if ( n >= 20 + wire * 30 && n < 25 + wire * 30 )
			{
				index = 1;
			}
			else if ( n >= 25 + wire * 30 && n < 30 + wire * 30 )
			{
				index = 1;
			} 

			atom[n].x = wire * bond_length;
			atom[n].y = 0.0;
			atom[n].z = chain_idx * bond_length;
			atom[n].idx = index;
			orientation[n].x = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].y = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].z = RAND_IN(-0.2,0.2);
			orientation[n].idx = index;
			chain_idx++;
		}
	}
		
	fprintf( left_data, "%i    %2.4f\n", 5 * num_wires, atom[29].z + bond_length );		
	fprintf( wire_data, "%i    %2.4f\n", 20 * num_wires, atom[29].z + bond_length );
	fprintf( right_data, "%i    %2.4f\n", 5 * num_wires, atom[29].z + bond_length );
	for (int wire = 0; wire < num_wires; wire++ )
	{
		for ( int i = wire * 30; i < 5 + wire * 30; i++ )
		{
			fprintf(left_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(left_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}

		for ( int i = 5 + wire * 30; i < 25 + wire * 30; i++ )
		{
			fprintf(wire_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(wire_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x, orientation[i].y, orientation[i].z);
		}	

		for ( int i = 25 + wire * 30; i < 30 + wire * 30; i++ )
		{
			fprintf(right_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(right_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}
	}
	

	printf("Finished writing data. \n");

	fclose(wire_data);
	fclose(left_data);
	fclose(right_data);
}

void varying_length( int length_wire = 5, int length_bacteria = 5, int num_wires = 1 )
{
	printf("You have selected a varying length output! \n");

	vector4 atom[1000];
	vector4 orientation[1000];

	FILE *wire_data = fopen("center_data.dat","w");
	FILE *left_data = fopen("left_data.dat","w");
	FILE *right_data = fopen("right_data.dat","w");

	int index = 1;

	int num_chain_particles = 3 * (length_wire + length_bacteria);

	for ( int wire = 0; wire < num_wires; wire++ )
	{
		int chain_idx = 0;
		for ( int n = wire * num_chain_particles; n < num_chain_particles + wire * num_chain_particles; n++ )
		{

			if ( n >= wire * num_chain_particles && n < length_wire + wire * num_chain_particles)
			{
				index = 1;
			}
			else if ( n >= length_bacteria + wire * num_chain_particles && n < length_bacteria + length_wire + wire * num_chain_particles)
			{
				index = 2;
			}
			else if ( n >= length_bacteria + length_wire + wire * num_chain_particles && n < length_wire + length_bacteria + length_wire + wire * num_chain_particles )
			{
				index = 1;
			}
			else if ( n >= length_wire + length_bacteria + length_wire + wire * num_chain_particles && n < 2 * (length_bacteria + length_wire) + wire * num_chain_particles )
			{
				index = 2;
			}
			else if ( n >= 2 * (length_bacteria + length_wire) + wire * num_chain_particles && n < 2 * (length_wire + length_bacteria) + length_wire + wire * num_chain_particles )
			{
				index = 1;
			}
			else if ( n >= 2 * (length_wire + length_bacteria) + length_wire + wire * num_chain_particles && num_chain_particles + wire * num_chain_particles )
			{
				index = 1;
			}
 
			atom[n].x = wire * bond_length;
			atom[n].y = 0.0;
			atom[n].z = chain_idx * bond_length;
			atom[n].idx = index;
			orientation[n].x = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].y = 1.0 + RAND_IN(-0.2,0.2);
			orientation[n].z = RAND_IN(-0.2,0.2);
			orientation[n].idx = index;
			chain_idx++;
		}
	}
		
	fprintf( left_data, "%i    %2.4f\n", length_wire * num_wires, atom[num_chain_particles - 1].z + bond_length );		
	fprintf( wire_data, "%i    %2.4f\n", 2 * (length_wire + length_bacteria) * num_wires, atom[num_chain_particles - 1].z + bond_length );
	fprintf( right_data, "%i    %2.4f\n", length_wire * num_wires, atom[num_chain_particles - 1].z + bond_length );
	for (int wire = 0; wire < num_wires; wire++ )
	{
		for ( int i = wire * num_chain_particles; i < length_wire + wire * num_chain_particles; i++ )
		{
			fprintf(left_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(left_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}

		for ( int i = length_wire + wire * num_chain_particles; i <  2 * (length_wire + length_bacteria) + length_wire + wire * num_chain_particles; i++ )
		{
			fprintf(wire_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(wire_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x, orientation[i].y, orientation[i].z);
		}	

		for ( int i =  2 * (length_wire + length_bacteria) + length_bacteria + wire * num_chain_particles; i < num_chain_particles + wire * num_chain_particles; i++ )
		{
			fprintf(right_data, "    %2.4f    %2.4f    %2.4f    %i\n", atom[i].x, atom[i].y, atom[i].z, atom[i].idx );
			// fprintf(right_data, "    %2.4f    %2.4f    %2.4f\n", orientation[i].x,orientation[i].y, orientation[i].z);
		}
	}
	

	printf("Finished writing data. \n");
	printf("Total particle number: %i \n", num_wires * ( 2 * (length_wire + length_bacteria) + 2 * length_wire) );


	fclose(wire_data);
	fclose(left_data);
	fclose(right_data);
}

void random_configuration( int num_wires )
{
	printf("You have selected a random output! \n");

	int choice = round(RAND_IN(0, 2));

	if ( num_wires == 1 )
	{
		if ( choice == 0 )
		{
			uniform_linear();
		}
		else if ( choice == 1 )
		{
			nonuniform_linear();
		}
		else if ( choice == 2 )
		{
			varying_length(round(RAND_IN(0,5)), round(RAND_IN(0,5)));
		}
	} 
	else 
	{
		if ( choice == 0 )
		{
			uniform_linear(num_wires);
		}
		else if ( choice == 1 )
		{
			nonuniform_linear(num_wires);
		}
		else if ( choice == 2 )
		{
			varying_length(round(RAND_IN(0,5)), round(RAND_IN(0,5)), num_wires);
		}
	}
}

int main ( int argc, char* argv[] )
{

	srand(time(NULL));

	string argv_string = argv[1];

	if ( argc < 2 )
	{
		printf("Incorrect arguments. Enter 'help' for more information.");
	}
	else if ( argc == 2 && argv_string.length() == 1)
	{
		if ( argv_string[0] == 'u' )
		{
			uniform_linear();
		}
		else if ( argv_string[0] == 'n' )
		{
			nonuniform_linear();
		}
		else if ( argv_string[0] == 'h' )
		{
			help_message();
		}
	}
	else if ( argc == 3 && argv_string.length() == 2 )
	{
		if ( argv_string[0] == 'u' && argv_string[1] == 'm' )
		{
			int num_wires = atoi(argv[2]);
			uniform_linear(num_wires);
		}
		else if ( argv_string[0] == 'n' && argv_string[1] == 'm' )
		{
			int num_wires = atoi(argv[2]);
			nonuniform_linear(num_wires);
		}
	}
	else if ( argc == 3  && argv_string.length() == 1 )
	{
		if ( argv_string[0] == 'r' )
		{
			int num_wires = atoi(argv[2]);
			random_configuration(num_wires);
		}
		else 
		{
			printf("Incorrect arguments.");
		}
	}
	else if ( argc == 4 )
	{
		if ( argv_string[0] == 'v' && argv_string.length() == 1 )
		{
			int wire_length=atoi(argv[2]);
			int bacteria_length=atoi(argv[3]);
			varying_length(wire_length, bacteria_length,1);
		}
	}
	else if ( argc == 5 )
	{
		if ( argv_string[0] == 'v' && argv_string.length() == 2 )
		{
			if ( argv_string[1] == 'm' )
			{
				int wire_length = atoi(argv[2]);
				int bacteria_length = atoi(argv[3]);
				int num_wires = atoi(argv[4]);
				varying_length(wire_length, bacteria_length, num_wires);
			}
			else
			{
				printf("Incorrect arguments.");
			}
		}
	}
	else 
	{
		printf("Incorrect arguments.");
		help_message();
	}

	return 0;
}