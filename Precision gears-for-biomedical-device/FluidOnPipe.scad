// ==========================================
// Linear & Discrete Fluid Flow Simulation
// Author: Your Name
// ==========================================
// To view animation: View > Animate 
// Recommended Settings: Steps: 24, FPS: 12

// Parameters
pipe_length = 60;
pipe_radius = 7;
wall_thickness = 1.2;
num_slugs = 6;         
total_steps = 24;      

// Quantized time variable
discrete_t = floor($t * total_steps) / total_steps;

// Render a hollow, transparent pipe
module pipe() {
    color("SlateGray", 0.25)
    render()
    difference() {
        cylinder(r = pipe_radius, h = pipe_length, center = true, $fn = 60);
        cylinder(r = pipe_radius - wall_thickness, h = pipe_length + 2, center = true, $fn = 60);
    }
}

// Render discrete fluid slugs
module discrete_fluid() {
    spacing = pipe_length / num_slugs;
    
    for (i = [0 : num_slugs - 1]) {
        offset = ((i * spacing + (discrete_t * pipe_length)) % pipe_length) - (pipe_length / 2);
        
        // Dynamic color shifting based on position for a sleek tech look
        hue_shift = (i / num_slugs);
        
        translate([0, 0, offset])
            color("DeepSkyBlue", 0.95)
            cylinder(r = pipe_radius - wall_thickness - 0.4, h = spacing * 0.6, center = true, $fn = 40);
    }
}

// Assemble scene
pipe();
discrete_fluid();
