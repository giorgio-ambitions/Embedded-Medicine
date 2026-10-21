// ==========================================================
// GREEK CANON / IDEALIZED - 8 HEADS PROPORTION MODEL
// ==========================================================

// --- Rendering Resolution ---
$fn = 32;

// --- Base Module Unit: 1 Head Height = 10 Units ---
head_h = 10; 

greek_ideal_mannequin();

module greek_ideal_mannequin() {
    color("ghostwhite") {
        
        // 1. HEAD (7.0 to 8.0 heads in overall height)
        translate([0, 0, 7.5 * head_h])
            sphere(r = head_h / 2);

        // 2. THORAX & CHEST (5.5 to 7.0 heads)
        translate([0, 0, 6.25 * head_h])
            cube([head_h * 2, head_h * 1.2, head_h * 1.5], center=true);

        // 3. PELVIS & HIPS (4.0 to 5.0 heads)
        translate([0, 0, 4.5 * head_h])
            cube([head_h * 1.6, head_h * 1.1, head_h * 1], center=true);

        // 4. LEGS (0.0 to 4.0 heads)
        // Right Leg (Engaged / Weight-bearing - straight)
        translate([head_h * 0.4, 0, 2 * head_h])
            cylinder(h = 4 * head_h, r1 = head_h * 0.35, r2 = head_h * 0.45, center=true);

        // Left Leg (Free / Relaxed - bent)
        translate([-head_h * 0.4, head_h * 0.2, 2 * head_h])
            rotate([5, -5, 0])
                cylinder(h = 4 * head_h, r1 = head_h * 0.35, r2 = head_h * 0.45, center=true);
                
        // 5. ARMS (4.5 to 6.5 heads)
        // Right Arm
        translate([head_h * 1.1, 0, 5.5 * head_h])
            rotate([0, 10, 0])
                cylinder(h = 2.5 * head_h, r = head_h * 0.25, center=true);

        // Left Arm
        translate([-head_h * 1.1, 0, 5.5 * head_h])
            rotate([0, -10, 0])
                cylinder(h = 2.5 * head_h, r = head_h * 0.25, center=true);
    }
}
