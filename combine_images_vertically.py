from PIL import Image

def combine_images_vertically(image_paths):
    images = [Image.open(path) for path in image_paths]

    # Check if the images list is empty
    if not images:
        return None  # Or raise an exception/error
    
    # Calculate total height and the maximum width
    total_height = sum(image.height for image in images)
    max_width = max(image.width for image in images)

    # Create a new image with the maximum width and total height
    combined_image = Image.new('RGBA', (max_width, total_height))

    # Paste each image into the combined image, aligning them to the left
    y_offset = 0
    for image in images:
        combined_image.paste(image, (0, y_offset))
        y_offset += image.height

    return combined_image

# Example usage
base_folder_path='SDL_Cmake/assets/'
length=6
image_paths=[]

image_paths.append(base_folder_path+"woman-idle/woman-idle.png")
image_paths.append(base_folder_path+"woman-walk/woman-walk.png")

combined_image = combine_images_vertically(image_paths)
if combined_image:
    combined_image.save('combined_image_vertical.png')
    # combined_image.show()  # Uncomment to display the image
