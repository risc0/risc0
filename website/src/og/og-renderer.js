const { readFileSync } = require("node:fs");
const { join } = require("node:path");

function renderer(data) {
  return [
    {
      type: "div",
      props: {
        style: {
          justifyContent: "center",
          alignItems: "center",
          background: "#FDFF9D",
          color: "#000",
          fontSize: "96px",
          width: "1440px",
          height: "900px",
          padding: "150px",
          display: "flex",
          textAlign: "center",
        },
        children: data.metadata.title,
      },
    },
    {
      width: 1440,
      height: 900,
      fonts: [
        {
          name: "Europa",
          data: readFileSync(join(__dirname, "./EuropaGroteskSH-Med.otf")),
          weight: 400,
          style: "normal",
        },
      ],
    },
  ];
}

module.exports = {
  renderer: renderer,
};
