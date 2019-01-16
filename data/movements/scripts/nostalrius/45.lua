function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		item:transform(430, 1)
		item:decay()
		Game.sendMagicEffect({x = 32468, y = 32119, z = 14}, 15)
		Game.sendMagicEffect({x = 32482, y = 32170, z = 14}, 15)
		Game.createItem(435, 1, {x = 32482, y = 32170, z = 14})
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(431, 1)
		item:decay()
		Game.sendMagicEffect({x = 32468, y = 32119, z = 14}, 14)
		Game.sendMagicEffect({x = 32482, y = 32170, z = 14}, 14)
		Game.removeItemOnMap({x = 32482, y = 32170, z = 14}, 435)
	end
end
