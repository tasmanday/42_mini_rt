/*

init pixel array - contains 5 rays, TL, TR, BL, BR, center, and an avg colour

init rays 5/pixel

iterate through pixels, use threads to split scene into quarters, pixels on top and LHS of quarters will need to process TR and BL rays, others can copy memory pointers

get ray directions

check object intersection to get distance and type of closest object

work out lighting and shadows to get colour of each ray

get average colour of each of the 5 rays per pixel for antialiasing

put pixels to image maybe with threads as well, one per image and loop through 3-4 different images

*/