namespace test_ext {
    export function thefunc() : number { 
        if (!inSimulator())
            return test_ext._thefunc()
        
        return 42
    }

    function inSimulator(): boolean {
        return control.deviceDalVersion() == "sim"
    }
}