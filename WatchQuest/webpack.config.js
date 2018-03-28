const { resolve } = require('path')

module.exports = {
  entry: {
    background: './src/background.js',
    popup: './src/popup.js',
    option: './src/option.js'
  },

  output: {
    path: resolve(__dirname, 'public'),
    filename: '[name].bundle.js'
  },

  devtool: 'inline-source-map',

  module: {
    rules: [
      {
        test: /.jsx?$/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: [ 'es2015', 'react', 'stage-0' ]
          }
        },
        include: resolve(__dirname, 'src')
      }
    ]
  }
}
