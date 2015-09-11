/**
 * Copyright (C) 2015, David Saenz Tagarro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <check.h>
#include "check_graph.h"
#include "check_queue.h"

int main(void)
{
        int nf;

        Suite *s0 = suite_create("Master");

        SRunner *sr = srunner_create(s0);
        srunner_add_suite (sr, make_graph_suite());
        srunner_add_suite (sr, make_queue_suite());

        srunner_run_all(sr, CK_ENV);
        nf = srunner_ntests_failed(sr);
        srunner_free(sr);

        return nf == 0 ? 0 : 1;
        return 0;
}
