{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs =
            with pkgs;
            [
              zsh
              nixfmt-rfc-style
              nil
              glsl_analyzer
              llvm_20
              cmake
            ]
            ++ lib.optional (pkgs.stdenv.isDarwin) apple-sdk_15;
        };
      }
    );
}
