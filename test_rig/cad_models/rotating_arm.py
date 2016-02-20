# This example is meant to be used from within the CadQuery module of FreeCAD.
import cadquery
import math
from Helpers import show

# The dimensions of the box. These can be modified rather than changing the
# object's code directly.
radius = 2.5 *1.04 # correction factor for J's 3D printer
halfWidth = 1.5 * 1.07 # correction factor for J's 3D printer
halfHeight = math.sqrt(math.pow(radius, 2) - math.pow(halfWidth, 2))

# The dimensions of the box. These can be modified rather than changing the
# object's code directly.
length = 20.0
height = 100.0
thickness = 3.0
post_dia = 4.9
post_height = 3.0
post_placement = height - 26.0 - post_dia

# Create a box based on the dimensions above and add a 22mm center hole
#result = cadquery.Workplane("XY").box(length, height, thickness) \
#    .faces(">Z").workplane().hole(center_hole_dia)
# r.faces(">Z").workplane()

r = cadquery.Workplane("XY").box(length, height, thickness)

r = r.faces(">Z").workplane().line(0, post_placement, True)\
    .circle(post_dia/2).extrude(post_height).faces(">Z").workplane()\
        .line(0, -2 * post_placement, True).circle(post_dia/2).extrude(-post_height)

r = r.cut(cadquery.Workplane("XY").line(halfWidth, 0, True).line(0, halfHeight)\
    .threePointArc((0, radius), (-halfWidth, halfHeight)).line(0, -halfHeight)\
        .mirrorX().extrude(thickness))

r = r.cut(cadquery.Workplane("XY").line(halfWidth, 0, True).line(0, halfHeight)\
    .threePointArc((0, radius), (-halfWidth, halfHeight)).line(0, -halfHeight)\
        .mirrorX().extrude(-thickness))


# Render the solid
show(r)
