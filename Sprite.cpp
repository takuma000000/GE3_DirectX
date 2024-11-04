#include "Sprite.h"
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include "MyMath.h"

void Sprite::Initialize(SpriteCommon* spriteCommon, DirectXCommon* dxCommon) {
	//引数で受け取ったメンバ変数に記録する
	this->spriteCommon = spriteCommon;
	dxCommon_ = dxCommon;

	//VertexResourceを作る
	vertexResource = dxCommon_->CreateBufferResource(sizeof(VertexData) * 4);
	//IndexResourceを作る
	indexResource = dxCommon_->CreateBufferResource(sizeof(uint32_t) * 6);
	//VertexBufferViewを作成する
	//Resourceの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//使用するResourceのサイズは頂点4つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 4;
	//1頂点あたりのサイズ
	vertexBufferView.StrideInBytes = sizeof(VertexData);
	//リソースの先頭のアドレスから使う
	indexBufferView.BufferLocation = indexResource->GetGPUVirtualAddress();
	//使用するリソースのサイズはインデックス6つ分のサイズ
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_tとする
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	//
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	indexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	//マテリアルリソースを作る
	materialResource = dxCommon->CreateBufferResource(sizeof(Material));
	//書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	//色は白に設定
	materialData->color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//SprightはLightingしないのでfalseを設定する
	materialData->enableLighting = false;
	materialData->uvTransform = MyMath::MakeIdentity4x4();

	//座標変換行列リソースを作る
	transformationMatrixResource = dxCommon->CreateBufferResource(sizeof(TransformationMatrix));
	//書き込むためのアドレスを取得
	transformationMatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData));
	//単位行列を書き込んでおく
	transformationMatrixData->wvp = MyMath::MakeIdentity4x4();
	transformationMatrixData->World = MyMath::MakeIdentity4x4();

}

void Sprite::Update() {
	//左下
	vertexData[0].position = { 0.0f,360.0f,0.0f,1.0f };
	vertexData[0].texcoord = { 0.0f,1.0f };
	vertexData[0].normal = { 0.0f,0.0f,-1.0f };
	//左上
	vertexData[1].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData[1].texcoord = { 0.0f,0.0f };
	vertexData[1].normal = { 0.0f,0.0f,-1.0f };
	//右上
	vertexData[3].position = { 640.0f,0.0f,0.0f,1.0f };
	vertexData[3].texcoord = { 1.0f,1.0f };
	vertexData[3].normal = { 0.0f,0.0f,-1.0f };
	//2枚目の三角形
	vertexData[2].position = { 640.0f,360.0f,0.0f,1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };
	vertexData[2].normal = { 0.0f,0.0f,-1.0f };

	//
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 1;
	indexData[4] = 3;
	indexData[5] = 2;

	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform cameraTransform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f} ,{0.0f,0.0f,-10.0f} };

	Matrix4x4 worldMatrixSprite = MyMath::MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MyMath::MakeIdentity4x4();
	Matrix4x4 projectionMatrixSprite = MyMath::MakeOrthographicMatrix(0.0f, 0.0f, float(WindowsAPI::kClientWidth), float(WindowsAPI::kClientHeight), 0.0f, 100.0f);

	transformationMatrixData->wvp = MyMath::Multiply(worldMatrixSprite, MyMath::Multiply(viewMatrixSprite, projectionMatrixSprite));
	transformationMatrixData->World = worldMatrixSprite;

	Transform transform;
	transform.translate = { position.x,position.y,0.0f };

}

void Sprite::Draw(D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU) {
	//VertexBufferViewを設定
	//Spriteの描画。変更が必要なものだけ変更する
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);//VBVを設定
	//TransformationMatrixCBufferの場所を設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResource->GetGPUVirtualAddress());
	//描画
	//dxCommon_->GetCommandList()->DrawInstanced(6, 1, 0, 0);

	//IndexBufferViewを設定
	//IBVを設定
	dxCommon_->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	//マテリアルCBufferの場所を設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//座標変換行列CBufferの場所を設定
	Transform uvTransformSprite{
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f},
	};

	Matrix4x4 uvTransformMatrix = MyMath::MakeScaleMatrix(uvTransformSprite.scale);
	uvTransformMatrix = MyMath::Multiply(uvTransformMatrix, MyMath::MakeRotateZMatrix(uvTransformSprite.rotate.z));
	uvTransformMatrix = MyMath::Multiply(uvTransformMatrix, MyMath::MakeTranslateMatrix(uvTransformSprite.translate));
	materialData->uvTransform = uvTransformMatrix;

	//SRVのDescriptorTableの先頭を設定
	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU);
	//描画。6個のインデックスを使用し1つのインスタンスを描画。その他は当面0で良い
	dxCommon_->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}