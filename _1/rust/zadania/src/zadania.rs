

fn zad2_0(path: &str) -> u32
{

}

fn zad2_1(path: &str) -> u32
{
    let file_str = fs::read_to_string(String::from(path)).unwrap();

    let line = String::from(file_str[0..file_str.rfind('\n').unwrap()+1]);
    let data_count: u32 = line.parse::<u32>().unwrap();

    let mut vec = Vec::new();
    vec.reserve(data_count);

    while !line.is_empty()
    {

    }
}

fn zad2_2(path: &str) -> u32
{

}