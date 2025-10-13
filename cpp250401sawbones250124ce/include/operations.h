#pragma once
#include "coordinate.h"

void scalpel(One_coordinate& coordinate_start, One_coordinate& coordinate_finish);
bool suture(One_coordinate& coordinate_start, One_coordinate& coordinate_finish, const One_coordinate& coordinates_scalpel_start, const One_coordinate& coordinates_scalpel_finish);
void hemostat(One_coordinate& coordinate);
void tweezers(One_coordinate& coordinate);
