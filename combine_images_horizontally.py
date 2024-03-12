from PIL import Image

def combine_images_horizontally(image_paths):
    images = [Image.open(path) for path in image_paths]

    # Assuming all images have the same dimensions
    if not images:
        return None  # Or raise an exception/error
    
    # Calculate total width and the common height
    total_width = sum(image.width for image in images)
    height = images[0].height

    # Create a new image with the calculated total width and the same height
    combined_image = Image.new('RGBA', (total_width, height))

    # Paste each image into the combined image
    x_offset = 0
    for image in images:
        combined_image.paste(image, (x_offset, 0))
        x_offset += image.width

    return combined_image

# Example usage
base_folder_path='SDL_Cmake/assets/'
length=7
image_paths=[]
for i in range(length):
    image_paths.append(base_folder_path+"woman-idle/woman-idle-"+str(i+1)+".png")

combined_image = combine_images_horizontally(image_paths)
if combined_image:
    combined_image.save('combined_image.png')
    # combined_image.show()  # Uncomment to display the image
