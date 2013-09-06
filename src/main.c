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

#include <src/argument.h>
#include <src/database.h>
#include <src/display.h>
#include <src/file.h>

#include <src/main.h>

int main(int argc, char *argv[])
{
	argument_build_system_list_from_arguments(argc, argv);

	database_init();

	char **argument_values = argument_get_argument_values_from_system_list();
	int arguments = argument_get_number_of_elements_in_system_list() - 1;

	populate_db_from_file("./raw/test.json");

	for(int i = 0; i < arguments; i += 1) {
		load_dot_scoutify(argument_values[i]);
	}

	merge_all();

	database_sort();

	database_display();
	database_display_table_mode();

	write_db_to_file("./raw/test.json");

	dump_database_to_csv_file("database.csv");
	
	return 0;
}
