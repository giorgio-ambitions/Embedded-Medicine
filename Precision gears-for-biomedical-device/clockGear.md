
//
// Custom 3D Printable Clock Gear
// Units: millimeters
//

$fn = 100;

// ---- Gear parameters ----
teeth = 24;             // Number of teeth
root_radius = 20;       // Radius of gear body
tooth_height = 4;       // Height of teeth
gear_thickness = 5;     // Thickness of gear
shaft_hole = 5;         // Center hole diameter

// ---- Calculated dimensions ----
outer_radius = root_radius + tooth_height;
tooth_width = (2 * PI * root_radius / teeth) * 0.55;

// ---- Gear model ----
difference() {
    linear_extrude(height = gear_thickness)
        union() {
            // Main circular gear body
            circle(r = root_radius);

            // Radial gear teeth
            for (i = [0 : teeth - 1]) {
                rotate(i * 360 / teeth)
                    translate([0, 0])
                        polygon(points = [
                            [-tooth_width/2, root_radius - 0.5],
                            [ tooth_width/2, root_radius - 0.5],
                            [ tooth_width*0.38, outer_radius],
                            [-tooth_width*0.38, outer_radius]
                        ]);
            }
        }

    // Center shaft hole
    translate([0, 0, -0.1])
        cylinder(
            h = gear_thickness + 0.2,
            d = shaft_hole
        );
}
