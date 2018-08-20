# Copyright (C) 2016 Model B, LLC.
# Designer: J. Simmons
#
# This documentation describes Open Hardware and is licensed under the CERN OHL v. 1.2.
#
# You may redistribute and modify this documentation under the terms of the CERN OHL v.1.2.
# (http://ohwr.org/cernohl). This documentation is distributed WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR
# PURPOSE. Please see the CERN OHL v.1.2 for applicable conditions.
#
# Documentation location: https://opendesignengine.net/projects/holoseat

# This example is meant to be used from within the CadQuery module of FreeCAD.
import cadquery
import math
from Helpers import show

# The dimensions of the box. These can be modified rather than changing the
# object's code directly.
radius = 2.5 * 1.04  # correction factor for J's 3D printer
halfWidth = 1.5 * 1.07  # correction factor for J's 3D printer
halfHeight = math.sqrt(math.pow(radius, 2) - math.pow(halfWidth, 2))

# The dimensions of the box. These can be modified rather than changing the
# object's code directly.
length = 20.0
height = 20.0
thickness = 6.0

pegSide = 13.20
pegHeight = 5.0 + thickness


r = cadquery.Workplane("XY").box(length, height, thickness,
                                 centered=(True, True, False))

r2 = cadquery.Workplane("XY").box(pegSide, pegSide, pegHeight,
                                 centered=(True, True, False))

r = r.union(r2)

r = r.cut(cadquery.Workplane("XY").line(halfWidth, 0, True).line(0, halfHeight)\
    .threePointArc((0, radius), (-halfWidth, halfHeight)).line(0, -halfHeight)\
        .mirrorX().extrude(thickness))

# Render the solid
show(r)
