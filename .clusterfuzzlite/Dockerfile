FROM ghcr.io/ledgerhq/ledger-app-builder/ledger-app-builder-lite:latest AS LITE_BUILDER

FROM gcr.io/oss-fuzz-base/base-builder:v1
COPY . $SRC/app-karlsen
COPY ./.clusterfuzzlite/build.sh $SRC/
COPY --from=LITE_BUILDER /opt/ledger-secure-sdk $SRC/app-karlsen/BOLOS_SDK
WORKDIR $SRC/app-karlsen