const ProductImage = require('../models/ProductImage');

const validateProductImageData = (imageData) => {
    if (!imageData.url) {
        throw new Error('Image URL is required.');
    }
};

exports.createProductImage = async (imageData) => {
    validateProductImageData(imageData);
    const productImage = new ProductImage(imageData);
    return await productImage.save();
};

exports.getAllProductImages = async () => {
    return await ProductImage.find();
};

exports.getProductImageById = async (imageId) => {
    const productImage = await ProductImage.findById(imageId);
    if (!productImage) throw new Error('Product image not found');
    return productImage;
};

exports.updateProductImage = async (imageId, updateData) => {
    validateProductImageData(updateData);
    const productImage = await ProductImage.findByIdAndUpdate(imageId, updateData, { new: true, runValidators: true });
    if (!productImage) throw new Error('Product image not found');
    return productImage;
};

exports.deleteProductImage = async (imageId) => {
    const productImage = await ProductImage.findByIdAndDelete(imageId);
    if (!productImage) throw new Error('Product image not found');
    return { message: 'Product image deleted successfully' };
};