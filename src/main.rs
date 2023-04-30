use std::io::{stderr, Write};

fn main() {
    const image_height: i32 = 256;
    const image_weight: i32 = 256;

    const max_color: i32 = 255;

    const max_color_f: f32 = 255.999;

    println!("P3 \n{} {} \n{}", image_weight, image_height, max_color);
    
    for h in (-1..image_height).rev() {
        eprintln!("Scanlines remaining: {}", h);
        stderr().flush().expect("Unable to flush sdterr");
        for w in 0..image_weight {
            let r = (w as f32) / ((image_height- 1) as f32);
            let g = (h as f32) / ((image_weight -1) as f32);
            let b = 0.25;

            let ir = (max_color_f * r) as i32;
            let ig = (max_color_f * g) as i32;
            let ib = (max_color_f * b) as i32;

            println!("{} {} {}", ir, ig, ib);
        }
    }
    eprintln!("Done!");
}
