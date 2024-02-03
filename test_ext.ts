namespace test_ext {
    export function thefunc() : number { 
        if (!inSimulator())
            return test_ext._thefunc()
        
        return 42
    }

    export function transposed(img:Image) : Image {
        if (!inSimulator())
            return test_ext._transposed(img)
        return img.transposed()
    }

    function inSimulator(): boolean {
        return control.deviceDalVersion() == "sim"
    }

    /**
     * Returns an image rotated by 90, 180, 270 deg clockwise
     */
    export function rotated(img: Image, deg: number) {
        if (deg == -90 || deg == 270) {
            let r = transposed(img);
            r.flipY();
            return r;
        } else if (deg == 180 || deg == -180) {
            let r = img.clone();
            r.flipX();
            r.flipY();
            return r;
        } else if (deg == 90) {
            let r = transposed(img);
            r.flipX();
            return r;
        } else {
            return null;
        }
    }
}