/*
    Copyright Christopher Cooper and Kristofer Rye 2013

    This file is part of scoutify-hub.

    scoutify-hub is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    scoutify-hub is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with scoutify-hub.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <src/argument.h>

argument_t *_root_argument_ = NULL;

argument_t *_argument_new_()
{ argument_t *ret = malloc(sizeof(argument_t));
	return ret;
}

argument_t *argument_new_from_data(int argc, char *argv)
{ argument_t *ret = _argument_new_();

	argument_set_data(ret, argc, argv);
	
	return ret;
}

argument_t *argument_new_from_data_after_argument(int argc, char *argv, argument_t *argument)
{ argument_t *ret = argument_new_from_data(argc, argv);

	argument_insert_after_argument(argument, ret);
	
	return ret;
}

void argument_insert_after_argument(argument_t *argument, argument_t *to_insert)
{
	if(argument->next != NULL) {
		printf("insertion detected previous next @0x%x w/ parent @0x%x\n", argument->next, argument);
		printf("%4s(we'll make a copy and then insert that as the next of the insertion)\n", "");

		argument_t *previous_next = argument->next;
		argument->next = to_insert;
		argument->next->next = previous_next;
	}
	
	argument->next = to_insert;
}

void argument_set_data(argument_t *argument, int index, char *value)
{
	argument->value = value;
	argument->index = index;
}

argument_t *argument_get_last_argument_in_system_list()
{
	argument_t *i = _root_argument_;

	while(i->next != NULL)
		i = i->next;

	return i;
}

void argument_build_system_list_from_arguments(int argc, char *argv[])
{
	_root_argument_ = argument_new_from_data(0, argv[0]);
	
	for(int i = 1; i < argc; i += 1) {
		argument_t *new = argument_new_from_data_after_argument(i, argv[i], argument_get_last_argument_in_system_list());
	}
}

void argument_debug_system_list()
{

	printf("DEBUG ARGLIST:\n");
	argument_t *i = _root_argument_;
	
	while(i != NULL) {
		printf("%4si => { %d [@ 0x%x] \"%s\" }\n", "", i->index, i, i->value);
		i = i->next;
	}

	argument_t *last = argument_get_last_argument_in_system_list();
	
	printf("%8slast dtctd == { %d [@0x%x] \"%s\" }\n", "", last->index, last, last->value);
}

int argument_get_number_of_elements_in_system_list()
{ int ret = 0;
	argument_t *i = _root_argument_;

	while(i != NULL) {
		ret += 1;
		i = i->next;
	}

	return ret;
}

argument_t *argument_system_list_get_nth_element(int n)
{ argument_t *argument = _root_argument_;
	int c = 0;
	while(c < n) {
		argument = argument->next;
		c += 1;
	}

	return argument;
}

argument_t **argument_get_array_of_argument_pointers_from_system_list()
{ argument_t **ret = malloc(sizeof(argument_t *) * argument_get_number_of_elements_in_system_list());
	unsigned int counter = 0;
	argument_t *i = _root_argument_;
	
	while(i != NULL) {
		ret[counter] = i;
		counter += 1;
		i = i->next;
	}
	
	return ret;
}

char **argument_get_values_from_system_list()
{ char **ret = malloc(sizeof(char *) * argument_get_number_of_elements_in_system_list() - 1);
	for(int i = 1; i < argument_get_number_of_elements_in_system_list(); i += 1) {
		ret[i - 1] = argument_system_list_get_nth_element(i)->value;
	}
	
	return ret;
}
