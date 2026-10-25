# Nhân hai đa thức trong trường hữu hạn GF(2⁴) và GF(2⁸)

**Sinh viên:** Nguyễn Trường Giang
**Môn:** Lý thuyết mật mã — Bài tập về nhà tuần 7

## Đề bài

Cài đặt thuật toán nhân 2 đa thức trong trường hữu hạn GF(2⁴), GF(2⁸) tương ứng với đa thức tối giản trong trường.

## Đa thức tối giản được chọn

| Trường | Đa thức tối giản m(x) | Dạng hex |
| --- | --- | --- |
| GF(2⁴) | x⁴ + x + 1 | 0x13 |
| GF(2⁸) | x⁸ + x⁴ + x³ + x + 1 (đa thức dùng trong AES) | 0x11B |

## Biểu diễn phần tử

Mỗi phần tử của GF(2ⁿ) là một đa thức bậc nhỏ hơn n, hệ số 0 hoặc 1. Đa thức được lưu thành một số nguyên, trong đó bit thứ i là hệ số của xⁱ.

Ví dụ: x³ + x + 1 ↔ `1011` ↔ `0xB`.

Cộng hai đa thức (hệ số lấy mod 2) chính là phép XOR.

## Thuật toán: dịch và cộng

```
r = 0
lặp n lần, duyệt từng bit của b từ thấp đến cao:
    nếu bit hiện tại của b = 1:  r = r XOR a
    a = a · x                    (dịch trái 1 bit)
    nếu a có bậc n:              a = a XOR m(x)   (rút gọn)
kết quả là r
```

Vì a·b = b₀·a + b₁·(a·x) + … + bₙ₋₁·(a·xⁿ⁻¹), biến `a` lần lượt mang giá trị a, a·x, a·x², … (đã rút gọn theo m(x)). Mỗi bit bᵢ = 1 sẽ cộng thêm đúng số hạng a·xⁱ vào kết quả.

Việc rút gọn diễn ra ngay trong vòng lặp. Khi a·x đạt bậc n, XOR với m(x) sẽ xóa bit xⁿ, vì trong trường ta có xⁿ = m(x) − xⁿ. Nhờ vậy giá trị trung gian không bao giờ vượt quá n bit.