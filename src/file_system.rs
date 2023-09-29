use core::ffi::c_void;

use alloc::{
    ffi::CString,
    string::{FromUtf8Error, String},
    vec,
    vec::Vec,
};
use libc;

pub enum FileOpenMode {
    Read,
    NewFileWrite,
    Append,
    ReadWrite,
    NewFileReadWrite,
    ReadAppend,
}

impl From<FileOpenMode> for CString {
    fn from(value: FileOpenMode) -> Self {
        match value {
            FileOpenMode::Read => CString::new("r").unwrap(),
            FileOpenMode::NewFileWrite => CString::new("w").unwrap(),
            FileOpenMode::Append => CString::new("a").unwrap(),
            FileOpenMode::ReadWrite => CString::new("r+").unwrap(),
            FileOpenMode::NewFileReadWrite => CString::new("w+").unwrap(),
            FileOpenMode::ReadAppend => CString::new("a+").unwrap(),
        }
    }
}

pub struct File(*mut libc::FILE);

impl File {
    pub fn open(file_name: &str, mode: FileOpenMode) -> Option<Self> {
        unsafe {
            let directory = CString::new(file_name).unwrap();
            let mode = CString::from(mode);

            let file_exists: i32 = libc::access(directory.as_ptr() as *const u8, 0);

            if file_exists == 0 {
                let file = libc::fopen(directory.as_ptr() as *const u8, mode.as_ptr() as *const u8);
                Some(File(file))
            } else {
                None
            }
        }
    }

    pub fn read(&self) -> Result<String, FromUtf8Error> {
        unsafe {
            let mut buf: Vec<u8> = vec![0; 128];
            libc::fread(buf.as_mut_ptr() as *mut c_void, 1, 128, self.0);
            String::from_utf8(buf)
        }
    }

    pub fn close(self) {
        drop(self);
    }
}

impl Drop for File {
    fn drop(&mut self) {
        unsafe {
            libc::fclose(self.0);
        }
    }
}
