use std::ffi::CStr;
use std::os::raw::{c_char, c_ulong};

#[no_mangle]
pub extern "C" fn safe_strcpy_rust(dest: *mut c_char, src: *const c_char, size: c_ulong) {
    unsafe {
        let src_str = CStr::from_ptr(src);
        let bytes = src_str.to_bytes();
        let copy_len = std::cmp::min(size as usize - 1, bytes.len());
        std::ptr::copy_nonoverlapping(bytes.as_ptr(), dest as *mut u8, copy_len);
        *dest.add(copy_len) = 0;
    }
}
