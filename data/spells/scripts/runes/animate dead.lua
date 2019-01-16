local humanBodies = {
	4240, 4241, 4247, 4248
}

function onCastSpell(creature, variant)
	local position = Variant.getPosition(variant)
	local tile = Tile(position)
	if tile then
		local corpse = tile:getTopDownItem()
		if corpse then
			local itemType = corpse:getType()
			if not table.contains(humanBodies, itemType:getId()) then
				if itemType:isCorpse() and itemType:isMovable() then
					local monster = Game.createMonster("Skeleton", position)
					if monster then
						corpse:remove()
						monster:setMaster(creature)
						position:sendMagicEffect(CONST_ME_MAGIC_BLUE)
						return true
					end
				end
			end
		end
	end

	creature:getPosition():sendMagicEffect(CONST_ME_POFF)
	creature:sendCancelMessage(RETURNVALUE_NOTPOSSIBLE)
	return false
end