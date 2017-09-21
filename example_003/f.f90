


subroutine sin_f90(x,ans) bind(C, name = "sin_f90")

	real, intent(in)  :: x
	real, intent(out) :: ans

	ans = sin(x)

end subroutine sin_f90

subroutine cos_f90(x,ans) bind(C, name = "cos_f90")

	real, intent(in)  :: x
	real, intent(out) :: ans

	ans = cos(x)

end subroutine cos_f90
