led_scale = 1.5;
leds_in_circle = 5;


//LED Dimensions
led_d=5; //LED Diameter
led_h=8; //LED Height
led_fh=1; //LED FLange Thickness
led_fd=5.5; //LED Flange Diameter
wire_d=2.5;//0.5; //Wire Diameter
wire_h=10; //Wire Height
wire_da=2; // THe distance between the Wires
module led(){
	union() {
		translate([0,0,led_fh-1])cylinder(led_h-(led_d/2)-led_fh+1,led_d/2,led_d/2, $fn=25);
		translate([0,0,led_h-(led_d/2)])sphere(led_d/2,  $fn=25);
		cylinder(led_fh,led_fd/2,led_fd/2, $fn=25);
		translate([0,wire_da/2,-wire_h])cylinder(wire_h+1,wire_d/2,wire_d/2, $fn=25);
		translate([0,wire_da/-2,-wire_h])cylinder(wire_h+1,wire_d/2,wire_d/2, $fn=25);

	}
}

module scaled_led() {
	scale([led_scale,led_scale,led_scale]) {
		led();
	}
}

led_hole_size = 2;
support_r = 7; //radius

module all_leds() {
	difference() {
		scale(0.7) union() {
			rotate([0,0,180/leds_in_circle]) cylinder(r=support_r*1.5, h=11,$fn=leds_in_circle);
			translate([0,0,support_r/2]) for(x=[0:1:leds_in_circle]) {
				angle = x * (360/leds_in_circle);
				rotate([0,0,angle]) {
					// rotate([0,45,0]){
					translate([support_r*1.5,0,0]) led_legs();
						// }
				}
			}
		}
		translate([0,0,5]) scaled_led();
	}
}



module led_leg() {
	rotate([90,90,0]) linear_extrude(wire_da, center=true) {
		difference() {
			union() {
				circle(support_r, $fn=100);		
				translate([-support_r,-support_r,0]) square([support_r*2,support_r], center=false);
				translate([0,-support_r,0]) square([support_r,support_r*2], center=false);
			}
			translate([support_r/2,-support_r,0]) square([support_r,support_r*2], center=false);
			translate([-support_r,-support_r,0]) square([support_r*2,support_r/2], center=false);
		}
	}
}

module led_legs() {
	y_distance = wire_da+led_hole_size;
	for(i=[-1:1:1]) {
		translate([0,i*y_distance,0]) {
			led_leg();
		}
	}
}

cube_size = ((support_r*2)+led_d)*2;
// projection()
all_leds();