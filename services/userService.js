const User = require('../models/User');
const bcrypt = require('bcrypt');

exports.authenticateUser = async (username, password) => {
    const user = await User.findOne({ username });
    if (!user) throw new Error('User not found');

    const isPasswordValid = await bcrypt.compare(password, user.password);
    if (!isPasswordValid) throw new Error('Invalid password');

    return user;
};

exports.createUser = async (userData) => {
    const hashedPassword = await bcrypt.hash(userData.password, 10);
    const user = new User({ ...userData, password: hashedPassword });
    return await user.save();
};