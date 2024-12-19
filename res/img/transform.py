import os
from PIL import Image

# 设置源文件夹
source_folders = ["prop"]

for source_folder in source_folders:
    if not os.path.exists(source_folder):
        print(f"目标文件夹, {source_folder}, 不存在")
        continue
    image_extensions = [".jpg", ".jpeg", ".png", ".gif", ".bmp", ".tiff"]
    current_foler = os.path.join(os.getcwd(), source_folder)
    print(f"当前文件夹: {current_foler}")
    image_files = [
        f
        for f in os.listdir(current_foler)
        if any(f.endswith(ext) for ext in image_extensions)
    ]
    print("将被处理的图片:", image_files)
    resolutions = [[100, 100], [80, 80], [60, 60]]
    # 处理每个分辨率
    for resolution in resolutions:
        # 处理每个图片
        for image_file in image_files:
            try:
                # 打开图片
                image_path = os.path.join(current_foler, image_file)
                with Image.open(image_path) as img:
                    # 调整图片大小
                    img_resized = img.resize((resolution[0], resolution[1]))
                    # 创建文件夹(如果不存在)
                    if not os.path.exists(
                        os.path.join(
                            current_foler,
                            f"{resolution[0] * 20}_{int(resolution[1] * 12.5)}",
                        )
                    ):
                        os.mkdir(
                            os.path.join(
                                current_foler,
                                f"{resolution[0] * 20}_{int(resolution[1] * 12.5)}",
                            )
                        )
                    # 保存到目标文件夹
                    save_path = os.path.join(
                        current_foler,
                        f"{resolution[0] * 20}_{int(resolution[1] * 12.5)}",
                        image_file,
                    )
                    img_resized.save(save_path)
                    print(f"图片 {image_file} 已成功调整并保存")
            except Exception as e:
                print(f"处理图片 {image_file} 时发生错误: {e}")
print("所有图片处理完成")
